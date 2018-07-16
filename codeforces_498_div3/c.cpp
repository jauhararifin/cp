#include <bits/stdc++.h>

using namespace std;

int n,a[200000];
unordered_map<long long,int> pos;
long long sum, ans;

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d", a + i);

  sum = 0;
  for (int i = 0; i < n; i++) {
    sum += 1LL * a[i];
    if (pos.find(sum) == pos.end()) {
      pos[sum] = i;
    }
  }

  ans = sum = 0;
  for (int i = n - 1; i >= 0; i--) {
    sum += 1LL * a[i];
    if (pos.find(sum) != pos.end() && pos[sum] < i)
      ans = max(ans, sum);
  }
  printf("%I64d\n", ans);

  return 0;
}