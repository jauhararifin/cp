#include <bits/stdc++.h>

using namespace std;

int n,x,ev,od;

int main() {
  scanf("%d", &n);
  ev = od = 0;
  for (int i = 0; i < n; i++) {
    scanf("%d", &x);
    if (x % 2) od++;
    else ev++;
  }
  printf("%d\n", min(od, ev));
  return 0;
}
