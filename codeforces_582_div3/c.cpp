#include <bits/stdc++.h>

using namespace std;

int q;
long long n,m;

int main() {
  scanf("%d", &q);
  while (q--) {
    scanf("%lld%lld", &n, &m);
    if (m > n) {
      printf("0\n");
      continue;
    }

    long long k = n/m;
    long long h = 0;
    long long ten = 0;
    for (long long i = 1; i <= 10; i++)
      ten += (m * i) % 10;
    h = ten * (k / 10);
    for (long long i = 1; i <= k%10; i++)
      h += (m * i) % 10;
    printf("%lld\n", h);
  }
  return 0;
}
