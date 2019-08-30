#include <bits/stdc++.h>

using namespace std;

int n;
char s[3], t[3];

char tmp[256];
bool bruteforce(int size, bool circular) {
  int top = 1;
  for (int i = 0; i < size; i++) top *= 3;

  for (int bm = 0; bm < top; bm++) {
    int x = bm;
    for (int i = 0; i < size; i++) {
      tmp[i] = x % 3;
      x /= 3;
    }

    int c[3]; memset(c, 0, sizeof c);
    for (int i = 0; i < size; i++) c[tmp[i]]++;
    if (c[0] != size/3 || c[1] != size/3 || c[2] != size/3) continue;

    bool check = 1;
    for (int i = 0; i < (circular ? size : size-1); i++)
      if ((tmp[i] == s[0] && tmp[(i+1)%size] == s[1]) || (tmp[i] == t[0] && tmp[(i+1)%size] == t[1]))
        check = 0;
    if (check)
      return 1;
  }
  return 0;
}

void solve() {
  scanf("%d%s%s", &n, s, t);
  s[0] -= 'a'; s[1] -= 'a'; t[0] -= 'a'; t[1] -= 'a';
  if (n <= 4) {
    bool res = bruteforce(n*3, 0);
    if (!res) {
      printf("NO\n");
      return;
    }

    printf("YES\n");
    for (int i = 0; i < n*3; i++)
      printf("%c", tmp[i] + 'a');
    printf("\n");
    return;
  }

  // 0 1
  // 0 2
  if (s[0] == t[0] && s[0] != s[1] && s[0] != t[1] && s[1] != t[1]) {
    printf("YES\n");
    for (int j = 0; j < n; j++) printf("%c%c", s[1] + 'a', t[1] + 'a');
    for (int i = 0; i < n; i++) printf("%c", s[0] + 'a');
    printf("\n");
    return;
  }

  // 1 0
  // 2 0
  if (s[1] == t[1] && s[1] != s[0] && t[1] != t[0] && s[0] != t[0]) {
    printf("YES\n");
    for (int i = 0; i < n; i++) printf("%c", s[1] + 'a');
    for (int j = 0; j < n; j++) printf("%c%c", s[0] + 'a', t[0] + 'a');
    printf("\n");
    return;
  }

  // 0 1
  // 1 0
  if (s[0] == t[1] && s[1] == t[0] && s[0] != s[1]) {
    int x = 0;
    while (x == s[0] || x == s[1]) x++;
    printf("YES\n");
    for (int i = 0; i < n; i++) printf("%c", s[0] + 'a');
    for (int i = 0; i < n; i++) printf("%c", x + 'a');
    for (int i = 0; i < n; i++) printf("%c", s[1] + 'a');
    printf("\n");
    return;
  }

  bool res = bruteforce(3, 1);
  if (!res) {
    printf("NO\n");
    return;
  }

  printf("YES\n");
  for (int i = 0; i < n; i++)
    printf("%c%c%c", tmp[0] + 'a', tmp[1] + 'a', tmp[2] + 'a');
  printf("\n");

  return;
}

int main() {
  solve();
  return 0;
}
