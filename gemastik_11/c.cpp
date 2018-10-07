#include <bits/stdc++.h>

using namespace std;

const long long mod = 1e9+7;

int t, n;
long long f[100001];

int main() {
    f[1] = 1;
    f[2] = 3;
    for (long long i = 3; i <= 100000; i++) {
        long long temp = (i * i) % mod;
        temp = (temp * f[i-1]) % mod;

        long long temp2 = ((i * (i - 1)) / 2) % mod;
        temp2 = (temp2 * (i - 1)) % mod;
        temp2 = (temp2 * f[i-2]) % mod;

        f[i] = (((temp - temp2) % mod) + mod) % mod;
    }
    
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        printf("%lld\n", f[n] % mod);
    }
    return 0;
}