#include <bits/stdc++.h>

using namespace std;

int t,n,m,a,c;

int main() {
  scanf("%d", &t);
  while(t--) {
    scanf("%d%d", &n, &m);
    c = 0;
    for (int i = 0; i < n; i++) {
      scanf("%d", &a);
      c += a % m == 0;
    }
    printf("%d\n", (1<<c)-1);
  }
  return 0;
}