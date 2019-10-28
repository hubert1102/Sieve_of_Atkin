//
// Created by Hubert on 27.10.2019.
//

#ifndef SIEVE_OF_ATKIN_SIEVEOFATKIN_H
#define SIEVE_OF_ATKIN_SIEVEOFATKIN_H
#include <map>
using namespace std;
#define BITSET_SIZE (1ULL<<25ULL)

void sieveOfAtkin(long long lowerB, long long upperB, map <long long, long long> &noOfPrimes);
#endif //SIEVE_OF_ATKIN_SIEVEOFATKIN_H
