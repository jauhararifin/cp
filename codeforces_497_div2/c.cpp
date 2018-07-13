#include <bits/stdc++.h>

using namespace std;

int n,a[100000];

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d", a + i);

  sort(a, a + n);
  int p = 0;
  for (int i = 0; i < n; i++)
    if (a[i] > a[p])
      p++;
  printf("%d\n", p);

  return 0;
}