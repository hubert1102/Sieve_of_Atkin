#include <iostream>
#include <map>
#include "sieveOfAtkin.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    map <long long, long long> noOfPrimes;

    unsigned long long N, upper_bound;
    cin >> N >> upper_bound;
    long long maxV = 0, V[N];

    for (size_t i = 0; i < N; i++) {
        cin >> V[i];
        noOfPrimes[V[i]] = 0;
        maxV = max(maxV, V[i]);
    }

    (*noOfPrimes.lower_bound(2)).second++;
    (*noOfPrimes.lower_bound(3)).second++;
    (*noOfPrimes.lower_bound(5)).second++;

    sieveOfAtkin(7, maxV, noOfPrimes);

    long long sum = 0;

    auto it = noOfPrimes.begin();
    for (; it != noOfPrimes.end(); ++it) {
        sum += (*it).second;
        (*it).second = sum;
    }
    for (long long v : V)
        cout << noOfPrimes[v] << endl;


    return 0;
}