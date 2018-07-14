#include <bits/stdc++.h>

using namespace std;

int n,c,a,b;

int main() {
  scanf("%d", &n);
  c = 2000000000;
  while (n--) {
    scanf("%d%d", &a, &b);
    if (c < a && c < b) {
      printf("NO\n");
      return 0;
    }
    if (a > c) c = b;
    else if (b > c) c = a;
    else c = max(a,b);
  }
  printf("YES\n");
  return 0;
}