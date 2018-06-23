#include <bits/stdc++.h>

using namespace std;

int n;
char p[2][101];

int memo[101];
int f(int s) {
  if (s >= n - 1) return 0;
  if (memo[s] > -1) return memo[s];
  int ans = 0;
  if (s < n - 2 && p[0][s] == '0' && p[1][s] == '0' && p[0][s+1] == '0' && p[1][s+1] == '0' && p[0][s+2] == '0' && p[1][s+2] == '0')
    ans = max(ans, 2 + f(s + 3));
  if (p[0][s] == '0' && p[1][s] == '0' && p[0][s+1] == '0')
    ans = max(ans, 1 + f(s + 2));
  if (p[0][s] == '0' && p[1][s] == '0' && p[1][s+1] == '0')
    ans = max(ans, 1 + f(s + 2));
  if (p[0][s] == '0' && p[0][s+1] == '0' && p[1][s+1] == '0')
    ans = max(ans, 1 + f(s + 2));
  if (p[1][s] == '0' && p[0][s+1] == '0' && p[1][s+1] == '0')
    ans = max(ans, 1 + f(s + 2));
  ans = max(ans, f(s + 1));
  return memo[s] = ans;
}

int main() {
  scanf("%s%s", p[0], p[1]);
  n = (int) strlen(p[0]);
  memset(memo, -1, sizeof memo);
  printf("%d\n", f(0));
  return 0;
}