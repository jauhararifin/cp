#include <bits/stdc++.h>

using namespace std;

int n,m,p[200000],c;
unordered_map<int,int> mp;
long long h;

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
    scanf("%d", p + i);

  for (int i = 0; i < n; i++)
    if (p[i] == m) {
      m = i;
      break;
    }

  c = 0;
  for (int i = m; i < n; i++) {
    if (p[i] < p[m]) c--;
    if (p[i] > p[m]) c++;
    mp[c]++;
  }

  c = 0;
  h = 0;
  for (int i = m; i >= 0; i--) {
    if (p[i] < p[m]) c--;
    if (p[i] > p[m]) c++;
    h += (long long) mp[-c] + (long long) mp[-c+1];
  }
  printf("%lld\n", h);
  
  return 0;
}