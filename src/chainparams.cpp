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
        pchMessageStart[0] = 0xb2;
        pchMessageStart[1] = 0xe7;
        pchMessageStart[2] = 0x1a;
        pchMessageStart[3] = 0x6d;
        vAlertPubKey = ParseHex("049d754d07e4ebaab5f1a52cec6c376f2bc3d3d0fa997528d2757afac9260aa29dcb60bb274a511477f263c722080794c848df46fcf59d7090e5b4553a2183468f");
        nDefaultPort = 18550;
        nRPCPort = 18551;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "THE BIRTH OFF DIMINUTIVE COIN 20191223";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1462595940, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1462595940;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 30362;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x61220f0732fec7c775b856c22aa59865dcf369533734f12364d4c9554fb85c77"));
        assert(genesis.hashMerkleRoot == uint256("0xb43068be1eb55051040ef038defaaecf59ae6ef2f2624961b5fb5b7973e209f7"));



        vSeeds.push_back(CDNSSeedData("seed1.dimi.net","51.75.162.95"));   // Connection Main 1 
	vSeeds.push_back(CDNSSeedData("seed5.dimi.net","51.38.71.12"));    // Connection Main 2
	


       base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 30);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 31);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 181);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x1A)(0x22)(0xAB)(0x5D).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3E)(0x27)(0xBA)(0xD5).convert_to_container<std::vector<unsigned char> >();

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
        vAlertPubKey = ParseHex("044f5f2b6f089f344e914721a0b986d095e436c06535e2a83604feb0e3bb892fe64884a98fdb73178b7aa73e44c1401428d54c9a4c34d1001bc6c27d488f19b6c4");
        nDefaultPort = 18550;
        nRPCPort = 18551;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 18887;
        genesis.nTime = 1462595940;

        hashGenesisBlock = genesis.GetHash();
      


assert(hashGenesisBlock == uint256("0x5a31658bcca40965f5381cea7b8211df68d862c5e0b727b9799b3bd79d564e17"));

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
        genesis.nTime = 1462595940;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 1;

        hashGenesisBlock = genesis.GetHash();

        nDefaultPort = 28500;
        strDataDir = "regtest";


        assert(hashGenesisBlock == uint256("0xf80042183e02437cf0b74ed7a39ed72aae02293a655c7a72b7f0fc2269cc8464"));


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
