#include <bits/stdc++.h>

using namespace std;

char s[200001],t[200001];

int main() {
  scanf("%s%s", s, t);
  int ns = (int) strlen(s);
  int nt = (int) strlen(t);
  reverse(s, s + ns);
  reverse(t, t + nt);
  int ans; for (ans = 0; ans < min(ns, nt) && s[ans] == t[ans]; ans++);
  printf("%d\n", ns + nt - 2 * ans);
  return 0;
}