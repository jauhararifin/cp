#include <bits/stdc++.h>

using namespace std;

int n,k,p[200000],q[200000],r[200001];
char ans[200001];

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++) scanf("%d", p + i);
  for (int i = 0; i < n; i++) scanf("%d", q + i);

  for (int i = 0; i < n; i++) r[q[i]] = i;

  vector<int> v;
  int curr = 0;
  int last_idx = -1;
  for (int i = 0; i < n; i++) {
    v.push_back(curr);
    last_idx = max(last_idx, r[p[i]]);
    if (i == last_idx) curr++;
  }

  for (int i = 0; i < n; i++)
    if (v[i] >= k) v[i] = k-1;

  if (curr < k) printf("NO\n");
  else {
    printf("YES\n");
    for (int i = 0; i < n; i++) ans[p[i]-1] = v[i] + 'a';
    ans[n] = 0;
    printf("%s\n", ans);
  }

  return 0;
}
