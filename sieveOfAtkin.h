#ifndef SIEVEOFATKIN_H
#define SIEVEOFATKIN_H

#include <map>

using namespace std;

// BITSET_SIZE can be increased to compute larger intervals.
// Currently calculates prime numbers up to 1.1 * 10^8
#define BITSET_SIZE (1ULL<<25ULL)
#define LL long long
#define ULL unsigned long long

/* For a map with keys in {a_1, a_2, ... , a_n} (a_k < a_(k+1)) and lowerB >= 1
 * computes number of primes in every (a_k, a_(k+1)] interval, storing it under a_(k+1) key.
 * a_(k+1) equals to upperB - 1.
 */
void sieveOfAtkin(LL lowerB, LL upperB, map <LL, LL> &noOfPrimes);

#endif //SIEVEOFATKIN_H
