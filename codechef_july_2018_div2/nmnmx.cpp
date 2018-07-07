#include <bits/stdc++.h>

using namespace std;

const long long mod = 1000000007LL;

int t,n,k,a[5000];

long long poww(long long a, long long b, long long mod) {
  if (b == 0) return 1LL;
  if (b == 1) return a % mod;
  long long c = poww(a, b / 2LL, mod) % mod;
  if (b % 2) return ((a % mod) * ((c * c) % mod)) % mod;
  return (c * c) % mod;
}

long long comb_memo[5001][5001];
long long comb(int n, int k, long long mod) {
  if (n < k) return 0;
  static bool loaded = 0;
  if (!loaded) {
    comb_memo[0][0] = comb_memo[1][0] = comb_memo[1][1] = 1LL;
    for (int i = 2; i <= 5000; i++) {
      comb_memo[i][0] = 1LL;
      for (int j = 1; j <= i; j++)
        comb_memo[i][j] = (comb_memo[i-1][j] + comb_memo[i-1][j-1]) % mod;
    }
    loaded = 1;
  }
  return comb_memo[n][k] % mod;
}

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++)
      scanf("%d", a + i);
    sort(a, a + n);

    long long result = 1LL;
    long long c = comb(n - 1, k - 1, mod - 1);
    for (int i = 0; i < n; i++) {
      long long mini = comb(i, k - 1, mod - 1);
      long long maxi = comb(n - i - 1, k - 1, mod - 1);
      long long total = (((c - mini - maxi) % (mod - 1)) + (mod - 1)) % (mod - 1);
      result = (result * poww(a[i], total, mod)) % mod;
    }
    printf("%lld\n", result % mod);
  }

  return 0;
}
