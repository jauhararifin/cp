#include <bits/stdc++.h>

using namespace std;

int n,m,a,b;

int main() {
  scanf("%d%d%d%d", &n, &m, &a, &b);
  printf("%d\n", max((n / a) * (m / b), (n / b) * (m / a)));
  return 0;
}