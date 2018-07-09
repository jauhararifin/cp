#include <bits/stdc++.h>

using namespace std;

int n,a[1000];
vector<int> ans;

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d", a + i);
  for (int i = 1; i < n; i++) {
    if (a[i] == 1)
      ans.push_back(a[i-1]);
  }
  ans.push_back(a[n-1]);
  printf("%d\n", (int) ans.size());
  for (int i = 0; i < (int) ans.size() - 1; i++)
    printf("%d ", ans[i]);
  printf("%d\n", ans.back());
}