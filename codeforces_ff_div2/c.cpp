#include <bits/stdc++.h>

using namespace std;

int n,a[100000],m[100000];

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) 
    scanf("%d", a + i);
  for (int i = 0; i < n;) {
    int j = 1;
    while (i+j < n && a[i+j] > a[i+j-1])
      j++;
    for (int k = 0; k < j; k++)
      m[i+k] = j - k; 
    i += j;
  }
  int h = 0;
  for (int i = 0; i < n; i++) 
    if (i + m[i] == n) 
      h = max(h, m[i]);
    else {
      int j = i + m[i];

      int ll = a[i+m[i]-1];
      int bll = m[i] == 1 ? -1 : a[i+m[i]-2];

      int fr = a[j];
      int afr = m[j] == 1 ? 2000000000 : a[j+1];

      if (afr - 1 > ll || bll + 1 < fr)
        h = max(h, m[i] + m[j]);
      else
        h = max(h, m[i] + 1);
    }
  printf("%d\n", h);
  return 0;
}
