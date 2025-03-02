// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2019 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SYSCOIN_NET_PROCESSING_H
#define SYSCOIN_NET_PROCESSING_H

#include <net.h>
#include <validationinterface.h>
#include <consensus/params.h>
#include <sync.h>
extern CCriticalSection cs_main;
// VIRCLES
/** Default for -maxorphantx, maximum number of orphan transactions kept in memory */
static const unsigned int DEFAULT_MAX_ORPHAN_TRANSACTIONS = 1000;
/** Default number of orphan+recently-replaced txn to keep around for block reconstruction */
static const unsigned int DEFAULT_BLOCK_RECONSTRUCTION_EXTRA_TXN = 1000;
static const bool DEFAULT_PEERBLOOMFILTERS = false;

class PeerLogicValidation final : public CValidationInterface, public NetEventsInterface {
private:
    CConnman* const connman;
    BanMan* const m_banman;

    bool CheckIfBanned(CNode* pnode) EXCLUSIVE_LOCKS_REQUIRED(cs_main);

public:
    PeerLogicValidation(CConnman* connman, BanMan* banman, CScheduler& scheduler);

    /**
     * Overridden from CValidationInterface.
     */
    void BlockConnected(const std::shared_ptr<const CBlock>& pblock, const CBlockIndex* pindexConnected, const std::vector<CTransactionRef>& vtxConflicted) override;
    /**
     * Overridden from CValidationInterface.
     */
    void UpdatedBlockTip(const CBlockIndex *pindexNew, const CBlockIndex *pindexFork, bool fInitialDownload) override;
    /**
     * Overridden from CValidationInterface.
     */
    void BlockChecked(const CBlock& block, const BlockValidationState& state) override;
    /**
     * Overridden from CValidationInterface.
     */
    void NewPoWValidBlock(const CBlockIndex *pindex, const std::shared_ptr<const CBlock>& pblock) override;

    /** Initialize a peer by adding it to mapNodeState and pushing a message requesting its version */
    void InitializeNode(CNode* pnode) override;
    /** Handle removal of a peer by updating various state and removing it from mapNodeState */
    void FinalizeNode(NodeId nodeid, bool& fUpdateConnectionTime) override;
    /**
    * Process protocol messages received from a given node
    *
    * @param[in]   pfrom           The node which we have received messages from.
    * @param[in]   interrupt       Interrupt condition for processing threads
    */
    bool ProcessMessages(CNode* pfrom, std::atomic<bool>& interrupt) override;
    /**
    * Send queued protocol messages to be sent to a give node.
    *
    * @param[in]   pto             The node which we are sending messages to.
    * @return                      True if there is more work to be done
    */
    bool SendMessages(CNode* pto) override EXCLUSIVE_LOCKS_REQUIRED(pto->cs_sendProcessing);

    /** Consider evicting an outbound peer based on the amount of time they've been behind our tip */
    void ConsiderEviction(CNode *pto, int64_t time_in_seconds) EXCLUSIVE_LOCKS_REQUIRED(cs_main);
    /** Evict extra outbound peers. If we think our tip may be stale, connect to an extra outbound */
    void CheckForStaleTipAndEvictPeers(const Consensus::Params &consensusParams);
    /** If we have extra outbound peers, try to disconnect the one with the oldest block announcement */
    void EvictExtraOutboundPeers(int64_t time_in_seconds) EXCLUSIVE_LOCKS_REQUIRED(cs_main);

private:
    int64_t m_stale_tip_check_time; //!< Next time to check for stale tip
};

struct CNodeStateStats {
    int nMisbehavior = 0;
    int nSyncHeight = -1;
    int nCommonHeight = -1;
    std::vector<int> vHeightInFlight;
};

/** Get statistics from node state */
bool GetNodeStateStats(NodeId nodeid, CNodeStateStats &stats);
// VIRCLES
extern bool IsAnnouncementAllowed(const CNode* pfrom, const int requestedAnnouncements, const uint256& hash)  EXCLUSIVE_LOCKS_REQUIRED(cs_main);
extern void RequestInv(const CNode* pfrom, const CInv &inv) EXCLUSIVE_LOCKS_REQUIRED(cs_main);
extern void EraseInvRequest(const CNode* pfrom, const uint256& hash) EXCLUSIVE_LOCKS_REQUIRED(cs_main);
/** Relay transaction to every node */
void RelayTransaction(const uint256&, const CConnman& connman);
#endif // SYSCOIN_NET_PROCESSING_H
