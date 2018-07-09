#include <bits/stdc++.h>

using namespace std;

int ns,h;
char s[200001];

int main() {
  scanf("%s", s);
  ns = (int) strlen(s);
  for (int i = 0; i < ns; i++) s[i] = (s[i] - '0') % 3;
  h = 0;
  for (int i = 0; i < ns; i++) {
    if (s[i] == 0)
      h++, s[i] = -1;
    else if (i > 1 && s[i] == 1 && s[i-1] == 1 && s[i-2] == 1)
      h++, s[i] = s[i-1] = s[i-2] = -1;
    else if (i > 0 && s[i] == 1 && s[i-1] == 2)
      h++, s[i] = s[i-1] = -1;
    else if (i > 0 && s[i] == 2 && s[i-1] == 1)
      h++, s[i] = s[i-1] = -1;
    else if (i > 1 && s[i] == 2 && s[i-1] == 2 && s[i-2] == 2)
      h++, s[i] = s[i-1] = s[i-2] = -1;
  }
  printf("%d\n", h);
}
