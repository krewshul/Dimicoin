// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 500;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
         ( 0,      uint256("0x2ce9a9e271caa8fc164d29ea497f60f0a0f6a05998db2430bc5003da148b6699") )
         ( 500,      uint256("0x000000000f7b5f8219b21c6b0bdcb3cf75a7eb1dd3caa38f5cdcfd66e8be2a46") )
         ( 1000,      uint256("0x00000000063816988ea0a483bf7457ef2f537a1134a04f3eaec7fc7e119b5da4") )
         ( 1500,      uint256("0x0000000046bec36becb71205861c5c4632dff80e246c57533d9948fbb596355a") )
         ( 2000,      uint256("0x0000000001437407968bb888bd1986adda3f00aac398e7166632281d1cf44fc2") )
         ( 2500,      uint256("0x0000000009469e6afd424963509c82d11943481fb2155675d360fa51803fd802") )
         ( 3000,      uint256("0x00000000ddd2f8ad358653779f7c9a5b5f235e630dc92d1d7041f8305c09af78") )
         ( 3500,      uint256("0x000000008d7c4bd424e8c089615a221e22b17c4e4c807cf32aba9f8d57ffbab0") )
         ( 4000,      uint256("0x000000000bb537e34c285f5149bb0ea7b37701aef358ee077a4e7e65d40d933c") )
         ( 4500,      uint256("0x00000000592b7a5ebec84a8ef1a213fd0beceaf5ff830ace71e98a3d1441c816") )
         ( 5000,      uint256("0x00000000515969771ce4f3dc665b30ccef5bd4528c51353aee471b2ea8e07877") )
         ( 5500,      uint256("0x000000000d5871b1c90c086ecfa5764a2cadd0ba561480b2fdbbe33ae117d76d") )
         ( 6000,      uint256("0x00000000438a554c32ea6a1def43be2edc0d335d482cecd3646f129381f96f12") )
         ( 6500,      uint256("0x0000000008aaf279a144c9fe085f76046eae800fe49e7743ef477cc1dea55946") ) //version 1002 Update
         ( 10000,      uint256("0x000000002c72a8a2b93e70d3a4aab03fd6b965fbac55e5dedd36ee14c24a9b8e") ) 
         ( 15000,      uint256("0x00000000221baa3fb004ecb3411cb4d0425dc167d6fc5f51e87a16e7d50bea37") ) 
         ( 16000,      uint256("0x000000001d9e894537c321cae49c9d652c0d5996ee8e74052f7a3e53c0c276dd") ) 
         ( 17000,      uint256("0x000000000f6eab27036fdc77d9a520f0df44737ab0d77e6ef469d9a076233b68") ) 
         ( 18000,      uint256("0x000000003edc980bd0d61b59eaf483e2d1fcf83bf04ed4df4aa63e848064daeb") ) 
         ( 20000,      uint256("0xd75b1c9bbae68bc5f1a556b82b851651a2bbd3701c0516bb6f4a34ae37425cc8") ) // Vevsion 1003 Update
         ( 30000,      uint256("0x000000001d239ebfbe7b8aa4a1660802d8304d71c9764cc1daa91363c8c3e2f3") )
         ( 40000,      uint256("0x0000000001077e21e70887f57c513da3c1d65f6f142f69901b423f818e96cc12") )
         ( 50000,      uint256("0x0000000007ea31edeeea9b5038047cac91639bfcac3f4876230deeb4e569449e") ) // Vevsion 1004 Update
                
        
         ;

    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();

        if (nHeight <= pindexSync->nHeight)
            return false;
        return true;
    }
}
