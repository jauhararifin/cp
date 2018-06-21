#include <bits/stdc++.h>

using namespace std;

int n,m,a[300000],b[300000];
stack<int> changes[300000];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
    scanf("%d", a + i);

  memset(b, 0, sizeof b);
  for (int i = 0; i < n; i++)
    b[a[i] % m]++;
  for (int i = 0; i < m; i++)
    b[i] -= n / m;

  stack<int> simpanan;
  for (int cycle = 0; cycle < 2; cycle++)
    for (int i = 0; i < m; i++) {
      if (b[i] > 0) {
        for (int j = 0; j < b[i]; j++)
          simpanan.push(i);
        b[i] = 0;
      } else if (b[i] < 0) {
        int x = min((int) simpanan.size(), -b[i]);
        b[i] += x;
        for (int j = 0; j < x; j++) {
          int f = simpanan.top(); simpanan.pop();
          changes[f].push(i);
        }
      }
    }
  
  long long langkah = 0;
  for (int i = 0; i < n; i++)
    if (!changes[a[i]%m].empty()) {
      int now = changes[a[i]%m].top(); changes[a[i]%m].pop();
      int initial = a[i] % m;
      int diff = (now + m - initial) % m;
      a[i] += diff;
      langkah += (long long) diff;
    }

  printf("%I64d\n%d", langkah, a[0]);
  for (int i = 1; i < n; i++)
    printf(" %d", a[i]);
  printf("\n");

  return 0;
}