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

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;
        
        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;
        
        memcpy(&ip, &t, sizeof(ip));
        
        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        //using HAVW in hex
        pchMessageStart[0] = 0x48;
        pchMessageStart[1] = 0x4d;
        pchMessageStart[2] = 0x43;
        pchMessageStart[3] = 0x57;
        vAlertPubKey = ParseHex("0466abe41dfd0702a639637ceae7c59d309d2876ca830017565e5a36925f4cbb6a52ef6d9d1b22727635feac128b3ff77821411b181268bc73b746aa823750ce79");
        nDefaultPort = 34787;
        nRPCPort = 34788;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        //CBlock(hash=0f1c683e664955996db18ef7d827d0ed69e168cf6055df8ea4ea7c80936d907c, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=3b6629fee8b425f74965a84b6c4e0c88732b041df879b1d5bf7f7db8981c4efc, nTime=1504607927, nBits=1e0ffff0, nNonce=450467, vtx=1, vchBlockSig=);
        //Coinbase(hash=12630d16a9, nTime=1504607927, ver=1, vin.size=1, vout.size=1, nLockTime=0);
        //CTxIn(COutPoint(0000000000, 4294967295), coinbase 4fd97621e34c6c637a837d1b2eefbb1922795d680130b270b7a30a547042d3c6);
        //CTxOut(empty);
        //vMerkleTree: 12630d16a9;
        const char* pszTimestamp = "08/10/2017 North Korea plans to test missile it thinks can reach US west coast"; 
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1504607927, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1507385546;
        genesis.nBits    = 504365040; 
        genesis.nNonce   = 168285;
        
        hashGenesisBlock = genesis.GetHash();
        
        //uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
        //while (genesis.GetHash() > hashTarget) {
        //    ++genesis.nNonce;
        //    if (genesis.nNonce == 0) { ++genesis.nTime; }
        //}
        //printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        //printf("genesis.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());
        //printf("new mainnet genesis nonce: %u\n", genesis.nNonce);
        //hashGenesisBlock = genesis.GetHash();
        
        assert(hashGenesisBlock == uint256("0x00000808365d4d0edb3e00d4c35ccce6d163524f2d806dbc9c39aeaf3ceb3339"));
        assert(genesis.hashMerkleRoot == uint256("0x681bf2132bda56f53a33f802bffa2324174c97ab849cd93c1abd71e2a03a9d30"));

        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,85);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,151);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,73);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x03)(0x88)(0xC3)(0x2E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x03)(0x88)(0xD3)(0xE2).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("0",  "seed0.havecoin.co"));
        vSeeds.push_back(CDNSSeedData("1",  "seed1.havecoin.co"));
        vSeeds.push_back(CDNSSeedData("2",  "seed2.havecoin.co"));
        vSeeds.push_back(CDNSSeedData("3",  "seed3.havecoin.co"));
        vSeeds.push_back(CDNSSeedData("4",  "seed4.havecoin.co"));
        vSeeds.push_back(CDNSSeedData("5",  "seed5.havecoin.co"));
        vSeeds.push_back(CDNSSeedData("6",  "seed6.havecoin.co"));
        vSeeds.push_back(CDNSSeedData("7",  "seed7.havecoin.co"));
        vSeeds.push_back(CDNSSeedData("8",  "seed8.havecoin.co"));
        vSeeds.push_back(CDNSSeedData("9",  "seed9.havecoin.co"));
        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nPoolMaxTransactions = 3;
        //strSporkKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
        //strMasternodePaymentsPubKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
        strDarksendPoolDummyAddress = "HH2GFeVtwHc6N41rxRHfTT9tqjmk9yDh1D";
        nLastPOWBlock = 1000;
        nPOSStartBlock = 1;
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
        pchMessageStart[0] = 0x48;
        pchMessageStart[1] = 0x4d;
        pchMessageStart[2] = 0x43;
        pchMessageStart[3] = 0x54;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0494a886a6c4470b0ef71c0c5e6eaf2133997ea675e9b778d9dd24c0d04fc4940bf960082c8e5073f68ef0f060129d3bb0d659185644cbe4d180b404847f26f972");
        nDefaultPort = 34707;
        nRPCPort = 34708;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = 504365040; 
        genesis.nNonce = 902858;
        
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xee5763d2d5a67b609436f58ae14fd926552fb28e53457c8ab91a7c5172280ca1"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,156);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,135);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,123);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,83);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x13)(0x06)(0x16)(0x27).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x13)(0x05)(0x17)(0x34).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 5000;
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
