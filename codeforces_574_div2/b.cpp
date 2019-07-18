#include <bits/stdc++.h>

using namespace std;

long long n,k;

long long sq(long long x) {
    long long i = 1;
    while (i*i < x) i++;
    return i;
}

int main() {
    scanf("%I64d%I64d", &n, &k);
    // p * (p + 1) / 2 - q = k
    // p*p + p - 2(n - p) = 2k
    // p^2 + 3p - 2n - 2k = 0
    // p + q = n
    long long p = (-3 + sq(9 + 8*(n+k)))/2;
    printf("%I64d\n", n - p);
    // 9 11
    // 
    return 0;
}