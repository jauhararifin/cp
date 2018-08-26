#include <bits/stdc++.h>

using namespace std;

int t,n,k;
bool used[100];

int main() {
  scanf("%d", &t);
  for (int tc = 1; tc <= t; tc++) {
    scanf("%d%d", &n, &k);
    memset(used, 0, sizeof used);
    vector<int> h;
    bool exists = 1;
    for (int i = 0; i < n; i++) {
      vector<int> v; for (int j = 0; j < i + 1; j++) {
        int x; scanf("%d", &x); x--; v.push_back(x);
      }
      sort(v.begin(), v.end());
      bool found = 0;
      for (int x : v)
        if (!used[x]) {
          used[x] = 1;
          h.push_back(x+1);
          found = 1;
          break;
        }
      if (!found) exists = 0;
    }
    printf("Kasus #%d:", tc);
    if (exists) {
      for (int x : h) printf(" %d", x);
      printf("\n");
    } else
      printf("Tidak ada pembagian\n");
  }
  return 0;
}