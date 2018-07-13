#include <bits/stdc++.h>

using namespace std;

char s[101];
int ns;

int main() {
  scanf("%s", s);
  ns = (int) strlen(s);
  for (int i = 0; i < ns; i++) {
    if (i == ns - 1 && s[i] != 'a' && s[i] != 'a' && s[i] != 'i' && s[i] != 'u' && s[i] != 'e' && s[i] != 'o' && s[i] != 'n') {
      printf("NO\n");
      return 0;
    }
    if (i < ns && s[i] != 'a' && s[i] != 'i' && s[i] != 'u' && s[i] != 'e' && s[i] != 'o' && s[i] != 'n' && s[i+1] != 'a' && s[i+1] != 'i' && s[i+1] != 'u' && s[i+1] != 'e' && s[i+1] != 'o') {
      printf("NO\n");
      return 0;
    }
  }
  printf("YES\n");
  return 0;
}