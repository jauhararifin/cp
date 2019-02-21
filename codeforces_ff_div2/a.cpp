#include <bits/stdc++.h>

using namespace std;

bool ht[300];
int p,n,x;

int main() {
  scanf("%d%d", &p, &n);
  memset(ht, 0, sizeof ht);
  for (int i = 0; i < n; i++) {
    scanf("%d", &x);
    if (ht[x % p]) {
      printf("%d\n", i+1);
      return 0;
    }
    ht[x % p] = 1;
  }
  printf("-1\n");
  return 0;
}
