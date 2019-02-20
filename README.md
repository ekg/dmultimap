# dmultimap

## a disk-backed dense multimap

_dmultimap_ is a disk-backed multimap where keys and values are stored in a binary file.
The key space is assumed to be numeric, but values may be of arbitrary size and type.
To build the multimap we first append key/value pairs.
To query the multimap we must first index it.
We first sort by key using an in-place disk backed binary radix sort (semi-parallel bsort).
Then we pad the key space so that we have one entry per integer in the range [0, max(keys)], sorting again to put the padding pairs in the right positions.
We record the key space by marking a bitvector of length equal to max(keys) with 1 at those positions corresponding to the first record of each key in the sorted array.
We compress this bitvector and build select supports on it.
We are now able to traverse the sorted array using select queries on this bitvector.
By memory mapping the backing file, we can achieve best-case performance even with multimaps that are larger than main memory.
See `src/main.cpp` for example usage.
Assuming dense keys, we can build a dmultimap for 100M elements in about 30 seconds on a laptop with an SSD.

## author

Erik Garrison

## license

MIT
