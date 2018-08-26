#include <bits/stdc++.h>

using namespace std;

const long long mod = 1000000007;

typedef struct {
    int n;
    int* par;
} disjoin_set;

disjoin_set init_disjoin_set(int n) {
    disjoin_set ds; ds.n = n;
    ds.par = new int[n];
    for (int i = 0; i < n; i++) ds.par[i] = i;
    return ds;
}

int parent_disjoin_set(disjoin_set ds, int x) {
    if (ds.par[x] == x) return x;
    return ds.par[x] = parent_disjoin_set(ds, ds.par[x]);
}

void union_disjoin_set(disjoin_set ds, int a, int b) {
    if (parent_disjoin_set(ds, a) < parent_disjoin_set(ds, b))
        ds.par[parent_disjoin_set(ds, b)] = parent_disjoin_set(ds, a);
    else
        ds.par[parent_disjoin_set(ds, a)] = parent_disjoin_set(ds, b);
}

void delete_disjoin_set(disjoin_set ds) {
    delete [] ds.par;
}

int t,n,m;
long long f[4000001];

int main() {
  f[0] = 1;
  for (int i = 1; i <= 4000000; i++)
    f[i] = (i * f[i-1]) % mod;

  scanf("%d", &t);
  for (int tc = 1; tc <= t; tc++) {
    scanf("%d%d", &n, &m);
    disjoin_set ds = init_disjoin_set(n);
    for (int i = 0; i < m; i++) {
      int x,y; scanf("%d%d", &x, &y); x--; y--;
      union_disjoin_set(ds, x, y);
    }

    map<int,int> mp;
    for (int i = 0; i < n; i++)
      mp[parent_disjoin_set(ds, i)]++;
    
    long long h = 1;
    int x = 0;
    for (auto i = mp.begin(); i != mp.end(); i++) {
      if (i->second > 1)
        h = (h * f[(i->second * (i->second - 1))/2]) % mod, x++;
    }
    h = (h * f[x]) % mod;
    printf("Kasus #%d: %lld\n", tc, h);

    delete_disjoin_set(ds);
  }
  return 0;
}