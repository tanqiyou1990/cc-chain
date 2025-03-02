// Copyright (c) 2014-2017 The Dash Core developers
// Copyright (c) 2017-2018 The Bitcoin Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SYSCOIN_ACTIVEMASTERNODE_H
#define SYSCOIN_ACTIVEMASTERNODE_H

#include <chainparams.h>
#include <key.h>
#include <net.h>
#include <primitives/transaction.h>

class CActiveMasternode;

static const int ACTIVE_MASTERNODE_INITIAL          = 0; // initial state
static const int ACTIVE_MASTERNODE_SYNC_IN_PROCESS  = 1;
static const int ACTIVE_MASTERNODE_INPUT_TOO_NEW    = 2;
static const int ACTIVE_MASTERNODE_NOT_CAPABLE      = 3;
static const int ACTIVE_MASTERNODE_STARTED          = 4;

extern CActiveMasternode activeMasternode;

// Responsible for activating the Masternode and pinging the network
class CActiveMasternode
{
public:
    enum masternode_type_enum_t {
        MASTERNODE_UNKNOWN = 0,
        MASTERNODE_REMOTE  = 1
    };

private:
    // critical section to protect the inner data structures
    mutable CCriticalSection cs;

    masternode_type_enum_t eType;

    bool fPingerEnabled;
    

    //  sentinel ping data
    int64_t nSentinelPingTime;
    uint32_t nSentinelVersion;

public:
    // Keys for the active Masternode
    CPubKey pubKeyMasternode;
    CKey keyMasternode;

    // Initialized while registering Masternode
    COutPoint outpoint;
    CService service;

    int nState; // should be one of ACTIVE_MASTERNODE_XXXX
    std::string strNotCapableReason;
    /// Ping Masternode
    bool SendMasternodePing(CConnman& connman);

    CActiveMasternode()
        : eType(MASTERNODE_UNKNOWN),
          fPingerEnabled(false),
          pubKeyMasternode(),
          keyMasternode(),
          outpoint(),
          service(),
          nState(ACTIVE_MASTERNODE_INITIAL)
    {}

    /// Manage state of active Masternode
    void ManageState(CConnman& connman);

    std::string GetStateString() const;
    std::string GetStatus() const;
    std::string GetTypeString() const;

    int nPingRetries = 0;           // add by luke 2020-4-28
    int GetPingRetries() const;     // add by luke 2020-4-28

    bool UpdateSentinelPing(int version);

    void DoMaintenance(CConnman &connman) { ManageState(connman); }

private:
    void ManageStateInitial(CConnman& connman);
    void ManageStateRemote();
};

#endif // SYSCOIN_ACTIVEMASTERNODE_H
