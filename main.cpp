#include <iostream>
#include <map>
#include "sieveOfAtkin.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    /* noOfPrimes[ n ] stores number of primes not bigger than n and bigger
       than the biggest smaller key than n in the map, if there is no such key
       it count from 1.
    */
    map <LL, LL> noOfPrimes;

    ULL N, upper_bound;
    cin >> upper_bound >> N;
    long long maxV = 0, V[N];

    for (size_t i = 0; i < N; i++) {
        cin >> V[i];
        noOfPrimes[V[i]] = 0;
        maxV = max(maxV, V[i]);
    }

    sieveOfAtkin(1, maxV + 1, noOfPrimes);

    LL sum = 0;

    auto it = noOfPrimes.begin();
    for (; it != noOfPrimes.end(); ++it) {
        sum += (*it).second;
        (*it).second = sum;
    }
    for (long long v : V)
        cout << noOfPrimes[v] << endl;


    return 0;
}