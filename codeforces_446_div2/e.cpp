#include <bits/stdc++.h>

#define fi first
#define se second
#define pii pair<int,int>
#define piii pair<int,pii>

using namespace std;

class disjoin_set {
public:
    disjoin_set(int n);
    disjoin_set(disjoin_set& ds);
    ~disjoin_set();
    int find(int x);
    int find(int v, int x);
    void join(int x, int y);
    void join(int v, int x, int y);
private:
    int n;
    int* par;
    int* ver; 
    disjoin_set *other;
};

disjoin_set::disjoin_set(int n) {
    this->n = n;
    ver = 0;
    other = 0;
    par = new int[n];
    for (int i = 0; i < n; i++) par[i] = i;
}

disjoin_set::disjoin_set(disjoin_set& ds) {
    n = ds.n;
    other = &ds;
    par = new int[n];
    ver = new int[n];
    for (int i = 0; i < n; i++) par[i] = i, ver[i] = -1;
}

disjoin_set::~disjoin_set() {
    delete [] par;
    if (ver)
        delete [] ver;
}

int disjoin_set::find(int x) {
    if (par[x] == x) return x;
    return par[x] = find(par[x]);
}

int disjoin_set::find(int v, int x) {
    if (ver[x] < v) {
        ver[x] = v;
        par[x] = other->find(x);
    }
    if (par[x] == x) return x;
    return par[x] = find(v, par[x]);
}

void disjoin_set::join(int x, int y) {
    if (find(x) < find(y))
        par[find(y)] = find(x);
    else
        par[find(x)] = find(y);
}

void disjoin_set::join(int v, int x, int y) {
    if (find(v, x) < find(v, y))
        par[find(v, y)] = find(v, x);
    else
        par[find(v, x)] = find(v, y);
}

int n,m,q,k;
piii edges[500000];
vector<int> egroup[500001];
set<pii> qgroup[500001];
bool ans[500000];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &edges[i].se.fi, &edges[i].se.se, &edges[i].fi);
        edges[i].se.fi--; edges[i].se.se--;
        egroup[edges[i].fi].push_back(i);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d", &k);
        while (k--) {
            int x; scanf("%d", &x); x--;
            qgroup[edges[x].fi].insert(make_pair(i,x));
        }
    }

    memset(ans, -1, sizeof ans);
    disjoin_set persistent_ds(n);
    disjoin_set temp_ds(persistent_ds);
    int version = 0;
    for (int i = 0; i <= 500000; i++) {
        int lastcase = -1;
        for (pii x : qgroup[i]) {
            if (lastcase != x.fi) version++;
            if (temp_ds.find(version, edges[x.se].se.fi) != temp_ds.find(version, edges[x.se].se.se))
                temp_ds.join(version, edges[x.se].se.fi, edges[x.se].se.se);
            else
                ans[x.fi] = 0;
            lastcase = x.fi;
        }
        for (int x : egroup[i])
            if (persistent_ds.find(edges[x].se.fi) != persistent_ds.find(edges[x].se.se))
                persistent_ds.join(edges[x].se.fi, edges[x].se.se);
    }
    for (int i = 0; i < q; i++)
        if (ans[i]) printf("YES\n");
        else printf("NO\n");

    return 0;
}