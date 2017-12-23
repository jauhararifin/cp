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

int main() {
    return 0;
}