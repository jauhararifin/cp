#include <bits/stdc++.h>

using namespace std;

int n,k,h[2000],l,sum;
pair<int,int> p[2000];

int main() {
  scanf("%d%d", &n,&k);
  for (int i = 0; i < n; i++)
    scanf("%d", &p[i].first), p[i].second = i;
  sort(p, p + n);
  reverse(p, p + n);
  sum = 0;
  for (int i = 0; i < k; i++) {
    h[i] = p[i].second;
    sum += p[i].first;
  }
  sort(h, h + k);
  l = -1;
  printf("%d\n", sum);
  for (int i = 0; i < k; i++) {
    if (i == k - 1)
      printf("%d\n", n - l - 1);
    else
      printf("%d ", h[i] - l);
    l = h[i];
  }
  return 0;
}