# Sievie_of_Atkin
Calculates the number of prime numbers in given intervals using Sieve of Atkin.

## Usage
### Build:
Type in the console in the directory containing the files:
```
cmake . 
cmake --build . 
```
to build. Then:
```
./Sieve_of_Atkin 
```
to run.

### Input-Output form:
Program reads from the standard input two positive integers upper_bound and N.
Then it reads N positive integers x_i, such that x_i <= upper_bound.
For each x_i the program prints to the standard output the number of primes in the (1, x_i] interval in the i-th row.

## Example:
For input:
```
200 4
50
100
150
200
```
The output is:
```
15
25
35
46
```
## Notes:
Line
```
#define BITSET_SIZE (1ULL<<25ULL)
```
found in [sieveOfAtkin.h](https://github.com/hubert1102/Sievie_of_Atkin/blob/master/sieveOfAtkin.h) defines the size of bitset used.
Current size allows for computing the number of prime numbers smaller than around 1.1 * 10^8. Resize if necessary.

## Referenes
Algorithm used is based on [Prime Sieves using Binary Quadratic Forms](http://cr.yp.to/papers/primesieves.pdf) by A.O.L Atkin, D.J.Bernstein.
