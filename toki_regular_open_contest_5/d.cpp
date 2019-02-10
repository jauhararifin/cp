#include <bits/stdc++.h>

using namespace std;

const long long mod = 1000000007LL;

int d,k;
long long n_bintree[100001];
long long memo[100001][11];

inline long long bintree(int l) {
    if (l < 1) return 0;
    return n_bintree[l];
}

long long solve(int level, int k) {
    if (k < 1)
        return 0LL;
    if (level == 1)
        return k == 1 ? 1LL : 0;
    if (memo[level][k] > -1)
        return memo[level][k];
    long long result = 0LL;
    for (int i = 1; i <= k-1; i++)
        result = (result + ((solve(level-1, i) % mod) * (solve(level-1, k-i) % mod)) % mod) % mod;
    result = result + (2 * (solve(level-1, k) * (bintree(level-2) + 1)) % mod) % mod;
    return memo[level][k] = result;
}

int main() {
    memset(memo, -1, sizeof memo);
    
    n_bintree[0] = 0;
    n_bintree[1] = 1;
    for (int i = 2; i <= 100000; i++) {
        n_bintree[i] = (n_bintree[i-1] * n_bintree[i-1]) % mod;
        n_bintree[i] = (n_bintree[i] + n_bintree[i-1] + n_bintree[i-1]) % mod;
        n_bintree[i] = (n_bintree[i] + 1LL) % mod;
    }

    scanf("%d%d", &d, &k);
    printf("%lld\n", solve(d,k) % mod);
    return 0;
}