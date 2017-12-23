#include <bits/stdc++.h>

using namespace std;

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

template<typename T>
vector<pair<T,pair<int,int> > > kruskal_mst(int n, vector<pair<T,pair<int,int> > > edges) {
    disjoin_set ds = init_disjoin_set(n);
    sort(edges.begin(), edges.end());
    vector<pair<T,pair<int,int> > > used_edges;
    int taken = 0;
    for (int i = 0; taken < n - 1 && i < (int) edges.size(); i++) {
        int a = edges[i].second.first; int b = edges[i].second.second;
        if (parent_disjoin_set(ds, a) != parent_disjoin_set(ds, b)) {
            union_disjoin_set(ds, a, b);
            taken++;
            used_edges.push_back(edges[i]);
        }
    }

    return used_edges;
}

int n,m;
vector<pair<long long,pair<int,int> > > edges;

int main() {
    scanf("%d%d", &n, &m);
    while (m--) {
        int a,b; long long c; scanf("%d%d%lld", &a, &b, &c); a--; b--;
        edges.push_back(make_pair(c, make_pair(a,b)));
    }
    vector<pair<long long,pair<int,int> > > mst = kruskal_mst(n, edges);
    long long size = 0LL;
    for (int i = 0; i < (int) mst.size(); i++)
        size += mst[i].first;
    printf("%lld\n", size);
    return 0;
}