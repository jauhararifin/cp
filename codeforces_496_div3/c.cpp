#include <bits/stdc++.h>

using namespace std;

int n,a[120000],h;
unordered_map<int,int> mp;

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d", a + i), mp[a[i]]++;
  
  h = 0;
  for (int i = 0; i < n; i++) {
    bool ada = 0;
    mp[a[i]]--;
    for (long long j = 1; j <= 2000000000LL && !ada; j <<= 1LL) {
      auto f = mp.find(j - a[i]);
      ada = f != mp.end() && f->second > 0;
    }
    mp[a[i]]++;

    if (!ada)
      h++;
  }
  printf("%d\n", h);

  return 0;
}