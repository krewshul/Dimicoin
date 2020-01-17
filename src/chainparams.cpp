// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x1e;
        pchMessageStart[1] = 0x3a;
        pchMessageStart[2] = 0x5a;
        pchMessageStart[3] = 0x3e;
        vAlertPubKey = ParseHex("0411c44368209451f52bf7f6c21e7c665ba508ffe7da0246d4e6e11355b9826f5d0c49b6293253ada51913a64d5b382c764bbf3ddbd21149535254a5c5c21fac98");
        nDefaultPort = 19550;
        nRPCPort = 19551;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "THE BIRTH OFF DIMINUTIVE COIN 20191223 V2";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1579107368, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1579107368;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 30362;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xf94a9208c76c9b74154b5342c9f0060982580fede1f6eb53741b1a33b70c8ddc"));
        assert(genesis.hashMerkleRoot == uint256("0xfddb73a7191af2c2ff18010f4548936ddab8ed2783023ff57ac9ad9157448b60"));

        vSeeds.push_back(CDNSSeedData("seed1.dimi.net","51.75.162.95"));   // Connection Main 1 
	vSeeds.push_back(CDNSSeedData("seed2.dimi.net","51.38.71.12"));    // Connection Main 2
	vSeeds.push_back(CDNSSeedData("seed3.dimi.net","167.86.94.93"));    // Connection Main 3
	
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 29);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 32);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 181);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x1D)(0x12)(0xED)(0xAD).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3A)(0xA7)(0x1A)(0xC5).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 8500000;   // Last Mineable block 
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xab;
        pchMessageStart[1] = 0xda;
        pchMessageStart[2] = 0x3d;
        pchMessageStart[3] = 0x5f;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("042568b05393011eaa32d1d47dabc8a0ab759425050e1e3a73d7c6e11a23148e52c034745592ff887fb48ef2a7e0c18b037e77c603d68d7246520c420850e3a0df");
        nDefaultPort = 18550;
        nRPCPort = 18551;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 18887;
        genesis.nTime = 1579107308;

        hashGenesisBlock = genesis.GetHash();

assert(hashGenesisBlock == uint256("0x681254110287a55db5d6999929f0f133c9dcb9beae9b03193eee8797563732ff"));

 vSeeds.push_back(CDNSSeedData("seed1.dimi.net","51.75.162.95"));   // Connection Main 1 
	vSeeds.push_back(CDNSSeedData("seed5.dimi.net","51.38.71.12"));    // Connection Main 2


      base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 114);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x41)(0x3B)(0xA7)(0x1F).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x14)(0x3C)(0xC3)(0xD4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xda;
        pchMessageStart[1] = 0x1a;
        pchMessageStart[2] = 0x9c;
        pchMessageStart[3] = 0x21;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1579107350;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 1;

        hashGenesisBlock = genesis.GetHash();


        nDefaultPort = 28500;
        strDataDir = "regtest";


        assert(hashGenesisBlock == uint256("0xd9362b559fdddc8fa24134d881bcde807e14b05091a803d888182b6a03db4594"));


        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
