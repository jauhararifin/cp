#include <bits/stdc++.h>

using namespace std;

class disjoin_set {
public:
    disjoin_set(int ns);
    disjoin_set(const disjoin_set &ds);
    void operator=(const disjoin_set &ds);
    ~disjoin_set();
    int find(int x);
    void join(int x, int y);
private:
    int n;
    int* par;
};

disjoin_set::disjoin_set(int n) {
    this->n = n;
    par = new int[n];
    for (int i = 0; i < n; i++) par[i] = i;
}

disjoin_set::disjoin_set(const disjoin_set& ds) {
    n = ds.n;
    par = new int[n];
    for (int i = 0; i < n; i++) par[i] = ds.par[i];
}

void disjoin_set::operator=(const disjoin_set &ds) {
    n = ds.n;
    delete [] par;
    par = new int[n];
    for (int i = 0; i < n; i++) par[i] = ds.par[i];
}

disjoin_set::~disjoin_set() {
    delete [] par;
}

int disjoin_set::find(int x) {
    if (par[x] == x) return x;
    return par[x] = find(par[x]);
}

void disjoin_set::join(int x, int y) {
    if (find(x) < find(y))
        par[find(y)] = find(x);
    else
        par[find(x)] = find(y);
}

int n,m;
long long cnt[200000],s[200001];
pair<int,pair<int,int> > edges[200000];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n-1; i++) {
    int u,v,w; scanf("%d%d%d", &u, &v, &w);
    u--; v--;
    edges[i] = {w,{u,v}};
  }
  sort(edges, edges+n-1);

  memset(s, 0, sizeof s);
  for (int i = 0; i < n; i++) cnt[i] = 1;
  disjoin_set ds(n);
  for (int i = 0; i < n-1; i++) {
    int x,y; tie(x,y) = edges[i].second;
    int w = edges[i].first;

    long long nx = cnt[ds.find(x)];
    long long ny = cnt[ds.find(y)];
    s[w] += nx * ny;
    ds.join(x,y);
    cnt[ds.find(x)] = nx + ny;
  }

  for (int i = 2; i <= 200000; i++)
    s[i] += s[i-1];

  vector<long long> ans;
  while (m--) {
    int x; scanf("%d", &x);
    ans.push_back(s[x]);
  }

  printf("%lld", ans[0]);
  for (int i = 1; i < (int) ans.size(); i++) printf(" %lld", ans[i]);
  printf("\n");

  return 0;
}
