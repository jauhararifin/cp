#include <bits/stdc++.h>

using namespace std;

int t,n,a[150000];

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    int mini = 1000000000;
    int h = 0;
    for (int i = n-1; i >= 0; i--) {
      if (a[i] > mini) h++;
      mini = min(mini, a[i]);
    }
    printf("%d\n", h);
  }
  return 0;
}
