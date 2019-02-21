#include <bits/stdc++.h>

using namespace std;

char s[1001];
int k,w[26];

int main() {
  scanf("%s%d", s, &k);
  for (int i = 0; i < 26; i++) scanf("%d", w + i);
  int m = 0; for (int i = 0; i < 26; i++) m = max(m, w[i]);
  int ns = (int) strlen(s);
  int h = 0;
  for (int i = 0; i < ns; i++)
    h += (i + 1) * w[s[i] - 'a'];
  for (int i = ns; i < ns + k; i++)
    h += (i + 1) * m;
  printf("%d\n", h);
  return 0;
}
