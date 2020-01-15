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
        ( 0,   uint256("0x61220f0732fec7c775b856c22aa59865dcf369533734f12364d4c9554fb85c77") ) // genesis
        ( 50,   uint256("0x00000000000001e46366cc8edf8c340c29c9342c6a95adca18c82f9565766184") )
        ( 100,   uint256("0x0000000000000151d30c9b4c3b9d3124ec3f62239ce9d99854965c36afa771bb") )
        ( 200,   uint256("0x000000000000036612d0dd4b7714d80e2ca15b054e4264aafc29cefc462121d5") )
        ( 300,   uint256("0x000000000000090b28874ac8eb823f986fe7280da07ad0f7b146d546bd05ede4") )
        ( 400,   uint256("0x000000000000059b87b5166a41be3a4e544265797d4fc4ec9dd7c5b9eb7d08fb") ) //Main Chain Check Point 1

	( 800,   uint256("0x00000000000002f44ebc1bb40d3df8a56c8ebaca07dd1c6b5936175361aeb739") )
	( 1000,   uint256("0x0000000000000edfc21e8d6e65a97442c02fc19373f4ba2cdf4afc9d2b783b10") )
	( 1200,   uint256("0x00000000000014342ec1d5ccfbb71f1b6fcb5362d89206d5ebcedc56ed0d9f55") )
	( 1400,   uint256("0x0000000000000c7d4aa37e2654a87473465b6cb1969fa9e6077887964b9e76ad") ) //Preparing for chain v2
	( 1550,   uint256("0x0000000000001e6da4c820ee68a2006e9887c49d06f2f9257363142940670031") ) //Preparing for chain v2
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
