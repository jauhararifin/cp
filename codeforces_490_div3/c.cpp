#include <bits/stdc++.h>

using namespace std;

int n,k,m[26],deleted[26];
char s[400001];

int main() {
  scanf("%d%d%s", &n, &k, s);
  memset(m, 0, sizeof m);
  for (int i = 0; i < n; i++)
    m[s[i]-'a']++;
  
  for (int i = 0; i < 26; i++) {
    int x = min(m[i], k);
    k -= x;
    deleted[i] = x;
  }
  for (int i = 0; i < n; i++)
    if (deleted[s[i]-'a']-- <= 0)
      printf("%c", s[i]);
  printf("\n");

  return 0;
}