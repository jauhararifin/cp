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

int main() {
    return 0;
}