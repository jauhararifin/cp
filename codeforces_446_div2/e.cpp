#include <bits/stdc++.h>

using namespace std;

namespace disjoin_set {
    typedef struct {
        int n;
        int* par;
    } disjoin_set;
    disjoin_set init(int n) {
        disjoin_set ds; ds.n = n;
        ds.par = new int[n];
        for (int i = 0; i < n; i++) ds.par[i] = i;
        return ds;
    }
    int parent(disjoin_set ds, int x) {
        if (ds.par[x] == x) return x;
        return ds.par[x] = parent(ds, ds.par[x]);
    }
    void uni(disjoin_set ds, int a, int b) {
        if (parent(ds, a) < parent(ds, b))
            ds.par[parent(ds, b)] = parent(ds, a);
        else
            ds.par[parent(ds, a)] = parent(ds, b);
    }
    void del(disjoin_set ds) {
        delete [] ds.par;
    }
}
template<typename T> vector<pair<T,pair<int,int> > > kruskal_mst(int n, vector<pair<T,pair<int,int> > > edges) {
    disjoin_set::disjoin_set ds = disjoin_set::init(n);
    sort(edges.begin(), edges.end());
    vector<pair<T,pair<int,int> > > used_edges;
    int taken = 0;
    for (int i = 0; taken < n - 1 && i < (int) edges.size(); i++) {
        int a = edges[i].second.first; int b = edges[i].second.second;
        if (disjoin_set::parent(ds, a) != disjoin_set::parent(ds, b)) {
            disjoin_set::uni(ds, a, b);
            taken++;
            used_edges.push_back(edges[i]);
        }
    }

    return used_edges;
}
namespace rmq {
    template<typename T>
    struct sparse_table {
        int n;
        int** st;
        T* a;
        bool store_minimum;
    };

    // sparse table store index
    template<typename T>
    sparse_table<T> generate_sparse_table(const vector<T>& arr, const bool store_minimum) {
        sparse_table<T> st;
        int n = (int) arr.size();
        st.n = n;
        st.a = new T[n];
        for (int i = 0; i < n; i++)
            st.a[i] = arr[i];
        st.st = new int*[n];
        for (int i = 0; i < n; i++) {
            st.st[i] = new int[(int)log2(n-i)+1];
            st.st[i][0] = i;
        }
        st.store_minimum = store_minimum;

        for (int j = 1; (1<<j) <= n; j++)
            for (int i = 0; i + (1<<j) - 1 < n; i++) {
                pair<T,int> a = make_pair(st.a[st.st[i][j-1]], st.st[i][j-1]);
                pair<T,int> b = make_pair(st.a[st.st[i+(1<<(j-1))][j-1]], st.st[i+(1<<(j-1))][j-1]);
                if (store_minimum)
                    st.st[i][j] = a.first < b.first ? a.second : b.second;
                else
                    st.st[i][j] = a.first > b.first ? a.second : b.second;
            }
        
        return st;
    }

    template<typename T>
    sparse_table<T> generate_sparse_table(const vector<T>& arr) { // default sparse table store minimum
        return generate_sparse_table(arr, true);
    }

    template<typename T>
    sparse_table<T> generate_sparse_table(int n, T* arr) {
        vector<T> v; for (int i = 0; i < n; i++) v.push_back(arr[i]);
        return generate_sparse_table(v);
    }

    // pair<index,value>, query on [from,to)
    template<typename T>
    pair<int,T> query_sparse_table(sparse_table<T> st, int from, int to) {
        to--;
        int k = (int) log2(to-from+1);
        pair<int,T> a = make_pair(st.st[from][k], st.a[st.st[from][k]]);
        pair<int,T> b = make_pair(st.st[to-(1<<k)+1][k], st.a[st.st[to-(1<<k)+1][k]]);
        if (st.store_minimum)
            return a.second <= b.second ? a : b;
        else
            return a.second >= b.second ? a : b;
    }

    template<typename T>
    void delete_sparse_table(sparse_table<T> st) {
        for (int i = 0; i < st.n; i++)
            delete [] st.st[i];
        delete [] st.st;
        delete [] st.a;
    }
}
void generate_euler_tour(int n, vector<pair<int,int> >* adjlist, pair<int,int> node, int before, vector<int> &output, vector<int>* occurence) {
    occurence[node.first].push_back(output.size());
    output.push_back(node.second);
    for (int i = 0; i < (int) adjlist[node.first].size(); i++)
        if (adjlist[node.first][i].first != before) {
            generate_euler_tour(n, adjlist, adjlist[node.first][i], node.first, output, occurence);
            occurence[node.first].push_back(output.size());
            output.push_back(adjlist[node.first][i].second);
        }
}

int n,m,q;
vector<pair<int,pair<int,int> > > edges,edges_persist;
vector<pair<int,int> > adjlist[500000];
vector<int> euler_tour, occurence[500000];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int x,y,z; scanf("%d%d%d", &x, &y, &z); x--; y--;
        edges.push_back(make_pair(z, make_pair(x,y)));
        edges_persist.push_back(make_pair(z, make_pair(x,y)));
    }
    vector<pair<int,pair<int,int> > > mst = kruskal_mst(n, edges);
    // for (int i = 0; i < (int) mst.size(); i++)
    //     printf("mst: %d %d %d\n", mst[i].first, mst[i].second.first, mst[i].second.second);

    for (int i = 0; i < (int) mst.size(); i++) {
        int w = mst[i].first; int a = mst[i].second.first; int b = mst[i].second.second;
        adjlist[a].push_back(make_pair(b,w));
        adjlist[b].push_back(make_pair(a,w));
    }
    generate_euler_tour(n, adjlist, make_pair(0,-1), -1, euler_tour, occurence);
    rmq::sparse_table<int> st = rmq::generate_sparse_table(euler_tour, false);

    // printf("euler tour:"); for (int i = 0; i < euler_tour.size(); i++) printf(" %d", euler_tour[i]); printf("\n");
    // printf("occurence:");
    // for (int i = 0; i < n; i++) {
    //     printf("%d ->", i);
    //     for (int j = 0; j < (int) occurence[i].size(); j++)
    //         printf(" %d", occurence[i][j]);
    //     printf("\n");
    // }

    scanf("%d", &q);
    while (q--) {
        int k, x; scanf("%d", &k);
        bool b = 1;

        disjoin_set::disjoin_set ds = disjoin_set::init(n);
        while (k--) {
            scanf("%d", &x); x--;
            int weight = edges_persist[x].first;
            int node_a = edges_persist[x].second.first;
            int node_b = edges_persist[x].second.second;
            if (b) {
                if (disjoin_set::parent(ds,node_a) == disjoin_set::parent(ds,node_b))
                    b = false;
                else
                    disjoin_set::uni(ds, node_a, node_b);
            }
            if (b) {
                int pa = occurence[node_a][0];
                int pb = occurence[node_b][0];
                int ppa = upper_bound(occurence[node_b].begin(), occurence[node_b].end(), pa) - occurence[node_b].begin() - 1;
                int ppb = upper_bound(occurence[node_a].begin(), occurence[node_a].end(), pb) - occurence[node_a].begin() - 1;
                int m;
                if (ppa >= 0) {
                    // printf("a %d %d\n", occurence[node_b][ppa] + 1, pa + 1);
                    m = rmq::query_sparse_table(st, occurence[node_b][ppa] + 1, pa + 1).second;
                } else {
                    // printf("b %d %d\n", occurence[node_a][ppb] + 1, pb + 1);
                    m = rmq::query_sparse_table(st, occurence[node_a][ppb] + 1, pb + 1).second;
                }
                // printf("query %d %d: %d\n", node_a, node_b, m);
                b = b && (m == weight);
            }
        }
        printf("%s\n", b ? "YES" : "NO");
        disjoin_set::del(ds);
    }

    return 0;
}