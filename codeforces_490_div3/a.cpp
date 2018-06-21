#include <bits/stdc++.h>

using namespace std;

int n,k,a[100];

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++)
    scanf("%d", a + i);

  int i = 0;
  int j = n - 1;
  int c = 0;
  while (i <= j && (a[i] <= k || a[j] <= k)) {
    if (a[i] <= k)
      i++;
    else
      j--;
    c++;
  }
  printf("%d\n", c);
  return 0;
}