#include <bits/stdc++.h>

using namespace std;

int n,k,a[200000];
vector<int> step[200001];

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++) scanf("%d", a + i);

  memset(step, 0, sizeof step);
  for (int i = 0; i < n; i++) {
    int x = a[i];
    int s = 0;
    while (x >= 1) {
      step[x].push_back(s);
      x >>= 1;
      s++;
    }
  }

  int h = 2000000000;
  for (int i = 1; i <= 200000; i++)
    if (step[i].size() >= k) {
      sort(step[i].begin(), step[i].end());
      int s = 0;
      for (int j = 0; j < k; j++) 
        s += step[i][j];
      h = min(h, s);
    }
  printf("%d\n", h);

  return 0;
}
