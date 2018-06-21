#include <bits/stdc++.h>

using namespace std;

int n;
char s[101];

int main() {
  scanf("%d%s", &n, s);
  for (int i = 1; i <= n; i++)
    if (n % i == 0) {
      reverse(s, s + i);
    }
  printf("%s\n", s);

  return 0;
}