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
        pchMessageStart[0] = 0x21;
        pchMessageStart[1] = 0x1a;
        pchMessageStart[2] = 0x2e;
        pchMessageStart[3] = 0x56;
        nDefaultPort = 49139;
        nRPCPort = 49122;
        //nDefaultPort = 16000;
       // nRPCPort = 16001;	    
	    
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
	const char* pszTimestamp = "Diminitivevault needs a new chain sha256 failed 20200121"; //
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1517516135, vin, vout, 0); // Thursday, February 1, 2018
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1517516135; // Thursday, February 1, 2018
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 5070141;

        hashGenesisBlock = genesis.GetHash();


        assert(hashGenesisBlock == uint256("0x2ce9a9e271caa8fc164d29ea497f60f0a0f6a05998db2430bc5003da148b6699"));
        assert(genesis.hashMerkleRoot == uint256("0x84346f5d939fa8c9d3548f3c3f31ef29f1b7972a43878453d3a5a4c176836459"));

        vSeeds.push_back(CDNSSeedData("seed1.dimi.net","51.75.162.95"));   // Connection Main 1 
	vSeeds.push_back(CDNSSeedData("seed2.dimi.net","51.38.71.12"));    // Connection Main 2
	vSeeds.push_back(CDNSSeedData("seed3.dimi.net","167.86.94.93"));    // Connection Main 3
      
       
	base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 32);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 30);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 181);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0xAD)(0x1B)(0x12)(0xA4).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0xE1)(0xA3)(0x2B)(0x3E).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

	nLastPOWBlock = 9999999999;

        
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
        pchMessageStart[0] = 0x15;
        pchMessageStart[1] = 0x5a;
        pchMessageStart[2] = 0xd5;
        pchMessageStart[3] = 0x21;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 8);
        nDefaultPort = 4913;
        nRPCPort = 4912;
	//nDefaultPort = 1600;
        //nRPCPort = 1601;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 612;
        
        hashGenesisBlock = genesis.GetHash();


        assert(hashGenesisBlock == uint256("0x644bb79bd649c703140975d3d73396951eacf3001c3b95dd1a2f50f5630cb293"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,117);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,115);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,63);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x14)(0x1a)(0x2c)(0x24).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x1f)(0xfa)(0x1e)(0x3e).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;

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

        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {

    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
