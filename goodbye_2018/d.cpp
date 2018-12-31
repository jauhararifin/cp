#include <bits/stdc++.h>

using namespace std;

int n;
long long h, p[1000001];
const long long mod = 998244353LL;

int main() {
    scanf("%d", &n);
    p[0] = 1;
    for (long long i = n; i >= 1; i--)
        p[n-i+1] = (p[n-i]*i) % mod;
    h = 1LL;
    for (int i = 0; i < n; i++)
        h = (h + p[n] - p[i]) % mod;
    printf("%lld\n", (h + mod) % mod);
    return 0;
}