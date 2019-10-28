//
// Created by Hubert on 27.10.2019.
//

#include "sieveOfAtkin.h"
#include <vector>
#include <algorithm>
#include <bitset>
#include <array>
#include <set>
#include <cmath>
#include <iostream>

using namespace std;

#define MOD 60
#define BASE 16

/* For d in {1,13,17,29,37,41,49,53}, 1 <= f <= 15, 1 <= g <= 30 and 4f^2 + g^2 ≡ d (mod 60)
 * executes algorithm 4.1 from the referenced paper. Marks all potential primes on the bitset.
 * For each potential prime increments a respective value in noOfPrimes.
 */
static void alg41(LL d, LL f, LL g, LL L, LL B, bitset <BITSET_SIZE> &isPrime,
                  LL dNo, map<LL, LL> &noOfPrimes) {
    LL  x = f, y0 = g, k0 = (4 * f * f + g * g - d) / MOD;

    while (MOD * k0 + d < B) {
        k0 += 2 * x + 15;
        x += 15;
    }
    while (true) {
        x -= 15;
        k0 -= (2 * x + 15);

        if (x <= 0)
            break;

        while (MOD * k0 + d < L) {
            k0 += y0 + 15;
            y0 += 30;
        }

        LL k = k0, y = y0;
        while (MOD * k + d < B) {
            isPrime[BASE * k + dNo].flip();

            // For every number marked as a potential prime we increment corresponding value in noOfPrimes.
            // If a number is unmarked as a potential prime, decrements the corresponding value in noOfPrimes.
            if (isPrime[BASE * k + dNo])
                (*noOfPrimes.lower_bound(MOD * k + d)).second++;
            else
                (*noOfPrimes.lower_bound(MOD * k + d)).second--;

            k += y + 15;
            y += 30;
        }
    }
}


/* For d in {7,19,31,43}, 1 <= f <= 10, 1 <= g <= 30 and 3f^2 + g^2 ≡ d (mod 60)
 * executes algorithm 4.2 from the referenced paper. Marks all potential primes on the bitset.
 * For each potential prime increments a respective value in noOfPrimes.
 */
static void alg42(LL d, LL f, LL g, LL L, LL B, bitset <BITSET_SIZE> &isPrime,
                  LL dNo, map<LL, LL> &noOfPrimes) {
    LL x = f, y0 = g, k0 = (3 * f * f + g * g - d) / MOD;

    while (MOD * k0 + d < B) {
        k0 += x + 5;
        x += 10;
    }

    while (true) {
        x -= 10;
        k0 -= x + 5;

        if (x <= 0)
            break;

        while (MOD * k0 + d < L) {
            k0 += y0 + 15;
            y0 += 30;
        }

        LL k = k0, y = y0;

        while (MOD * k + d < B) {
            isPrime[BASE * k + dNo].flip();

            // For every number marked as a potential prime we increment corresponding value in noOfPrimes.
            // If a number is unmarked as a potential prime, decrements the corresponding value in noOfPrimes.
            if (isPrime[BASE * k + dNo])
                (*noOfPrimes.lower_bound(MOD * k + d)).second++;
            else
                (*noOfPrimes.lower_bound(MOD * k + d)).second--;

            k += y + 15;
            y += 30;
        }
    }
}

/* For d in {11,23,47,59}, 1 <= f <= 10, 1 <= g <= 30 and 3f^2 - g^2 ≡ d (mod 60)
 * executes algorithm 4.3 from the referenced paper. Marks all potential primes on the bitset.
 * For each potential prime increments a respective value in noOfPrimes.
 */
static void alg43(LL d, LL f, LL g, LL L, LL B, bitset <BITSET_SIZE> &isPrime,
                  LL dNo, map<LL, LL> &noOfPrimes) {
    LL x = f, y0 = g, k0 = (3 * f * f - g * g - d) / MOD;

    while (true) {
        while (MOD * k0 + d >= B) {
            if (x <= y0)
                return;
            k0 -= y0 + 15;
            y0 += 30;
        }

        LL k = k0, y = y0;

        while (MOD * k + d >= L && y < x) {
            isPrime[BASE * k + dNo].flip();

            // For every number marked as a potential prime we increment corresponding value in noOfPrimes.
            // If a number is unmarked as a potential prime, decrements the corresponding value in noOfPrimes.
            if (isPrime[BASE * k + dNo])
                (*noOfPrimes.lower_bound(MOD * k + d)).second++;
            else
                (*noOfPrimes.lower_bound(MOD * k + d)).second--;

            k -= y + 15;
            y += 30;
        }

        k0 += x + 5;
        x += 10;
    }
}

void sieveOfAtkin(LL lowerB, LL upperB, map <LL, LL> &noOfPrimes) {
    /* Cell primes[16 * k + d], for d in {1, 2, ...m 15}, correspondes to the status of the number
     * 60k + d', where d' is the d-th  modulo 60 remainder, that's not divisable by 2, 3 or 5.
     * An array of booleans can be used for better memory for smaller upperB.
     */
    bitset <BITSET_SIZE> primes;


    // Handling primes dividing 60.
    (*noOfPrimes.lower_bound(2)).second++;
    (*noOfPrimes.lower_bound(3)).second++;
    (*noOfPrimes.lower_bound(5)).second++;

    const vector<LL> allRemainders = {{1,7,11,13,17,19,23,29,31,37,41,43,47,49,53,59}};
    const vector<LL> remainders[3] = {{1,13,17,29,37,41,49,53},
                                             {7,19,31,43},
                                             {11,23,47,59}};

    map<LL, LL> remainerNo = {{1, 0}, {7, 1} , {11, 2} , {13, 3} , {17, 4}, {19, 5},
                                            {23, 6}, {29, 7}, {31, 8}, {37, 9}, {41, 10}, {43, 11},
                                            {47, 12}, {49, 13}, {53, 14}, {59, 15}};

    // Computes all possible arguments {d, f, g} for functions alg41, alg42 and alg43.
    vector< array<LL, 3>> alg41_args;
    vector< array<LL, 3>> alg42_args;
    vector< array<LL, 3>> alg43_args;

    for (LL r : remainders[0]) {
        for (LL f = 1; f <= 15; f++) {
            for (LL g  = 1; g <= 30; g++)
                if ((4 * f * f + g * g) % MOD == r)
                    alg41_args.push_back({r, f, g});
        }
    }
    for (LL r : remainders[1]) {
        for (LL f = 1; f <= 10; f++) {
            for (LL g  = 1; g <= 30; g++)
                if ((3 * f * f + g * g) % MOD == r)
                    alg42_args.push_back({r, f, g});
        }
    }
    for (LL r : remainders[2]) {
        for (LL f = 1; f <= 10; f++) {
            for (LL g  = 1; g <= 30; g++)
                if ((((3 * f * f - g * g) % MOD) + MOD) % MOD == r)
                    alg43_args.push_back({r, f, g});
        }
    }

    /* Run functions alg41, alg42, alg43 for previously computed arguments
     * and the given interval. All potential primes will be marked as true
     * in bitset primes.
     */
    for (array<LL, 3> tuple : alg41_args)
        alg41(tuple[0], tuple[1], tuple[2], lowerB,
              upperB, primes, remainerNo[tuple[0]], noOfPrimes);
    for (array<LL, 3> tuple : alg42_args)
        alg42(tuple[0], tuple[1], tuple[2], lowerB,
              upperB, primes, remainerNo[tuple[0]], noOfPrimes);
    for (array<LL, 3> tuple : alg43_args)
        alg43(tuple[0], tuple[1], tuple[2], lowerB,
              upperB, primes, remainerNo[tuple[0]], noOfPrimes);


    /* Sieves off all squareful numbers. For all primes[y] changing it's
     * value to false, decrements the correspodning value in noOfPrimes.
     */
    for (size_t i = 1; ; i++) {

        // Convert number in 16k + d notation used in bitset primes to 60k + d' notation.
        LL n = (i - (i % BASE)) * MOD / BASE + allRemainders[i % BASE];
        if (n * n > upperB)
            break;

        for (LL j = n * n; j <= upperB; j += n * n) {
            if (remainerNo.count(j % MOD)) {

                // Convert number in 60k + d' notation to a number in 16k + d notation.
                LL y = (j - j % MOD) * BASE / MOD + remainerNo[j % MOD];
                if (primes[y]) {
                    primes[y] = false;
                    (*noOfPrimes.lower_bound(j)).second--;
                }
            }
        }
    }
}