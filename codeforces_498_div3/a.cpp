#include <bits/stdc++.h>

using namespace std;

int n, x;

int main() {
  scanf("%d", &n);
  while (n--) {
    scanf("%d", &x);
    printf("%d%c", x % 2 ? x : x - 1, n ? ' ' : '\n');
  }
  return 0;
}