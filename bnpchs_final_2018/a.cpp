#include <bits/stdc++.h>

using namespace std;

int t,n,a,b,k;

int main() {
  scanf("%d", &t);
  for (int tc = 1; tc <= t; tc++) {
    scanf("%d%d%d%d", &n, &a, &b, &k);
    printf("Kasus #%d: %d\n", tc, n + (b - a) * k);
  }
  return 0;
}