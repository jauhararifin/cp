#include <bits/stdc++.h>

using namespace std;

int n,m,q,par[500000],min_ed[500000];
vector<pair<int,pair<int,int> > > edges,edges_persist;
vector<pair<int,int> > adjlist[500000];

int find(int a) {
    if (par[a] != a)
        par[a] = find(par[a]);
    return par[a];
}

void uni(int x, int y) {
    if (find(y) < find(x))
        par[find(x)] = find(y);
    else
        par[find(y)] = find(x);
}

int min_edge(int node_a, int node_b) {

}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int x,y,z; scanf("%d%d%d", &x, &y, &z); x--; y--;
        edges.push_back(make_pair(z, make_pair(x,y)));
        edges_persist.push_back(make_pair(z, make_pair(x,y)));
    }
    sort(edges.begin(), edges.end());

    for (int i = 0; i < n; i++) par[i] = i;
    int ambil = 0;
    for (int i = 0; i < m && ambil < n-1; i++) {
        pair<int,int> ed = edges[i].second;
        int weight = edges[i].first;
        if (find(ed.first) != find(ed.second)) {
            ambil++;
            uni(ed.first, ed.second);
            adjlist[ed.first].push_back(make_pair(ed.second, weight));
            adjlist[ed.second].push_back(make_pair(ed.first, weight));
        }
    }

    // minimum edge between two vertex in tree

    // min_ed[0] = 0;
    // queue<pair<pair<int,int>,int> > que;
    // for (pair<int,int> neigh : adjlist[0])
    //     que.push(make_pair(make_pair(neigh.first,0),neigh.second));
    // while(!que.empty()) {
    //     pair<pair<int,int>,int> t = que.front(); que.pop();
    //     int node = t.first.first;
    //     int prev = t.first.second;
    //     int minimum = t.second;
    //     min_ed[node] = minimum;
    //     for (pair<int,int> neigh : adjlist[node])
    //         if (neigh.first != prev)
    //             que.push(make_pair(make_pair(neigh.first, node),min(neigh.second, minimum)));
    // }

    // build lca tree
    
    scanf("%d", &q);
    while (q--) {
        int k, x; scanf("%d", &k);
        bool b = 1;
        while (k--) {
            scanf("%d", &x); x--;
            int weight = edges_persist[x].first;
            int node_a = edges_persist[x].second.first;
            int node_b = edges_persist[x].second.second;
            if (b)
                b = b && (min_edge(node_a, node_b) == weight);
        }
        printf("%s\n", b ? "YES" : "NO");
    }

    return 0;
}