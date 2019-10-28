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

static void alg41(long long d, long long f, long long g, long long L, long long B,
           bitset <BITSET_SIZE> &isPrime, long long dNo, map<long long, long long> &noOfPrimes) {
    long long  x = f, y0 = g, k0 = (4 * f * f + g * g - d) / MOD;

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

        long long k = k0, y = y0;
        while (MOD * k + d < B) {
            isPrime[BASE * k + dNo].flip();
            if (isPrime[BASE * k + dNo])
                (*noOfPrimes.lower_bound(MOD * k + d)).second++;
            else
                (*noOfPrimes.lower_bound(MOD * k + d)).second--;

            k += y + 15;
            y += 30;
        }
    }
}

static void alg42(long long d, long long f, long long g, long long L, long long B,
           bitset <BITSET_SIZE> &isPrime, long long dNo, map<long long, long long> &noOfPrimes) {
    long long x = f, y0 = g, k0 = (3 * f * f + g * g - d) / MOD;

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

        long long k = k0, y = y0;

        while (MOD * k + d < B) {
            isPrime[BASE * k + dNo].flip();
            if (isPrime[BASE * k + dNo])
                (*noOfPrimes.lower_bound(MOD * k + d)).second++;
            else
                (*noOfPrimes.lower_bound(MOD * k + d)).second--;

            k += y + 15;
            y += 30;
        }
    }
}

static void alg43(long long d, long long f, long long g, long long L, long long B,
        bitset <BITSET_SIZE> &isPrime, long long dNo, map<long long, long long> &noOfPrimes) {
    long long x = f, y0 = g, k0 = (3 * f * f - g * g - d) / MOD;

    while (true) {
        while (MOD * k0 + d >= B) {
            if (x <= y0)
                return;
            k0 -= y0 + 15;
            y0 += 30;
        }

        long long k = k0, y = y0;

        while (MOD * k + d >= L && y < x) {
            isPrime[BASE * k + dNo].flip();
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

void sieveOfAtkin(long long lowerB, long long upperB, map <long long, long long> &noOfPrimes) {
    bitset <BITSET_SIZE> primes;
    const vector<long long> allRemainders = {{1,7,11,13,17,19,23,29,31,37,41,43,47,49,53,59}};
    const vector<long long> remainders[3] = {{1,13,17,29,37,41,49,53},
                                             {7,19,31,43},
                                             {11,23,47,59}};

    map<long long, long long> remainerNo = {{1, 0}, {7, 1} , {11, 2} , {13, 3} , {17, 4}, {19, 5},
                                            {23, 6}, {29, 7}, {31, 8}, {37, 9}, {41, 10}, {43, 11},
                                            {47, 12}, {49, 13}, {53, 14}, {59, 15}};
    vector< array<long long, 3>> alg41_input;
    vector< array<long long, 3>> alg42_input;
    vector< array<long long, 3>> alg43_input;

    for (long long r : remainders[0]) {
        for (long long f = 1; f <= 15; f++) {
            for (long long g  = 1; g <= 30; g++)
                if ((4 * f * f + g * g) % MOD == r)
                    alg41_input.push_back({r, f, g});
        }
    }
    for (long long r : remainders[1]) {
        for (long long f = 1; f <= 10; f++) {
            for (long long g  = 1; g <= 30; g++)
                if ((3 * f * f + g * g) % MOD == r)
                    alg42_input.push_back({r, f, g});
        }
    }
    for (long long r : remainders[2]) {
        for (long long f = 1; f <= 10; f++) {
            for (long long g  = 1; g <= 30; g++)
                if ((((3 * f * f - g * g) % MOD) + MOD) % MOD == r)
                    alg43_input.push_back({r, f, g});
        }
    }

    for (array<long long, 3> tuple : alg41_input)
        alg41(tuple[0], tuple[1], tuple[2], lowerB,
              upperB, primes, remainerNo[tuple[0]], noOfPrimes);
    for (array<long long, 3> tuple : alg42_input)
        alg42(tuple[0], tuple[1], tuple[2], lowerB,
              upperB, primes, remainerNo[tuple[0]], noOfPrimes);
    for (array<long long, 3> tuple : alg43_input)
        alg43(tuple[0], tuple[1], tuple[2], lowerB,
              upperB, primes, remainerNo[tuple[0]], noOfPrimes);



    for (size_t i = 1; ; i++) {
        long long n = (i - (i % BASE)) * MOD / BASE + allRemainders[i % BASE];
        if (n * n > upperB)
            break;

        for (long long j = n * n; j <= upperB; j += n * n) {
            if (remainerNo.count(j % MOD)) {
                long long y = (j - j % MOD) * BASE / MOD + remainerNo[j % MOD];
                if (primes[y]) {
                    primes[y] = false;
                    (*noOfPrimes.lower_bound(j)).second--;
                }
            }
        }
    }
}