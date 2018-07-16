#include <bits/stdc++.h>

using namespace std;

int n,h;
char s1[100001],s2[100001];

int main() {
  scanf("%d%s%s", &n, s1, s2);
  h = 0;
  for (int i = 0; i < n / 2; i++) {
    char p[4] = {s1[i], s1[n-i-1], s2[i], s2[n-i-1]};
    char q[4];
    q[2] = p[2];
    q[3] = p[3];
    int m = 4;
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++) {
        q[0] = p[i];
        q[1] = p[j];
        q[2] = p[2];
        q[3] = p[3];
        int cost = (q[0] != p[0] ? 1 : 0) + (q[1] != p[1] ? 1 : 0);
        sort(q, q + 4);
        if (q[0] == q[1] && q[2] == q[3]) m = min(m, cost);
      }
    h += m;
  }
  if (n % 2 && s1[n/2] != s2[n/2])
    h++;
  printf("%d\n", h);
  return 0;
}