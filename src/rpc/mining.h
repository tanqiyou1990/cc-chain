// Copyright (c) 2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SYSCOIN_RPC_MINING_H
#define SYSCOIN_RPC_MINING_H

#include <script/script.h>

#include <univalue.h>

#include <memory>

class AuxpowMiner;
/** Generate blocks (mine) */
UniValue generateBlocks(const CTxMemPool& mempool, std::shared_ptr<CReserveScript> coinbaseScript, int nGenerate, uint64_t nMaxTries, bool keepScript);

//add by luke
UniValue GenerateBitcoins(const CTxMemPool& mempool, std::shared_ptr<CReserveScript> coinbaseScript, bool fGenerate, int nThreads);
UniValue BitcoinMiner(const CTxMemPool& mempool, std::shared_ptr<CReserveScript> coinbaseScript);
void StopBitcoinMiner();

/** Singleton instance of the AuxpowMiner, created during startup.  */
extern std::unique_ptr<AuxpowMiner> g_auxpow_miner;

#endif
