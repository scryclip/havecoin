
Harvest development tree

Harvest is a PoS-based cryptocurrency.

HAV is dependent upon libsecp256k1 by sipa, the sources for which can be found here:
https://github.com/bitcoin/secp256k1

Total POW: 1000 Blocks

POS Reward: 3.5 HAV (HiPOS)

Masternode reward: 80% of POS

Block Spacing: 120 Seconds

Diff Retarget: 9 Blocks

Maturity: 10 Blocks

Stake Minimum Age: 1 Hours

5 MegaByte Maximum Block Size (5X Bitcoin Core)

Port: 34787
RPC Port: 34788

Magic Bytes: 0x48 0x4d 0x43 0x57

HAV includes an Address Index feature, based on the address index API (searchrawtransactions RPC command) implemented in Bitcoin Core but modified implementation to work with the HAV codebase (PoS coins maintain a txindex by default for instance).

Initialize the Address Index By Running with -reindexaddr Command Line Argument.  It may take 10-15 minutes to build the initial index.


