#include <bits/stdc++.h>

using namespace std;

long long n;

long long check(long long x) {
  long long valya = 0;
  long long half = (n + 1) / 2LL;
  long long remaining = n;
  while (remaining > 0) {
    long long valya_eat = min(x, remaining);
    remaining -= valya_eat;
    long long petya_eat = remaining / 10LL;
    remaining -= petya_eat;
    valya += valya_eat;
  }
  return valya >= half;
}

int main() {
  scanf("%I64d", &n);
  long long lo = 1LL;
  long long hi = max(lo, n / 2LL);
  long long ans = hi;
  while (lo <= hi) {
    long long mi = (lo + hi) / 2;
    if (check(mi)) {
      ans = mi;
      hi = mi - 1;
    } else
      lo = mi + 1;
  }
  printf("%I64d\n", ans);
  return 0;
}