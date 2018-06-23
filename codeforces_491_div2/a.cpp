#include <bits/stdc++.h>

using namespace std;

int a,b,c,n;

int main() {
  scanf("%d%d%d%d", &a, &b, &c, &n);
  if (c > a || c > b)
    printf("-1\n");
  else if (a + b - c  > n)
    printf("-1\n");
  else if (n - a - b + c > 0)
    printf("%d\n", n - a - b + c );
  else
    printf("-1\n");
  return 0;
}