#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct sparse_table {
    int n;
    int** st;
    T* a;
};

// sparse table store index
template<typename T>
sparse_table<T> generate_sparse_table(const vector<T>& arr) {
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

    for (int j = 1; (1<<j) <= n; j++)
        for (int i = 0; i + (1<<j) - 1 < n; i++)
            if (st.a[st.st[i][j-1]] < st.a[st.st[i+(1<<(j-1))][j-1]])
                st.st[i][j] = st.st[i][j-1];
            else
                st.st[i][j] = st.st[i+(1<<(j-1))][j-1];
    
    return st;
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
    if (st.a[st.st[from][k]] <= st.a[st.st[to-(1<<k)+1][k]])
        return make_pair(st.st[from][k], st.a[st.st[from][k]]);
    else
        return make_pair(st.st[to-(1<<k)+1][k], st.a[st.st[to-(1<<k)+1][k]]);
}

template<typename T>
void delete_sparse_table(sparse_table<T> st) {
    for (int i = 0; i < st.n; i++)
        delete [] st.st[i];
    delete [] st.st;
    delete [] st.a;
}

typedef struct {
    int n;
    int* first_appear;
    int* node_mapping;
    int* index_mapping;
    sparse_table<int> st;
} lca;

void generate_euler_tour(int n, vector<int>* adjlist, int node, int before, vector<int> &output, int* node_mapping, int* index_mapping, int& last_mapping) {
    if (node_mapping[node] < 0) {
        index_mapping[last_mapping] = node;
        node_mapping[node] = last_mapping++;
    }
    output.push_back(node_mapping[node]);
    for (int i = 0; i < (int) adjlist[node].size(); i++)
        if (adjlist[node][i] != before) {
            generate_euler_tour(n, adjlist, adjlist[node][i], node, output, node_mapping, index_mapping, last_mapping);
            output.push_back(node_mapping[node]);
        }
}

lca generate_lca(int n, vector<int>* adjlist, int root) {
    vector<int> euler_tour;
    int* node_mapping = (int*) malloc(n*sizeof(int));
    int* index_mapping = (int*) malloc(n*sizeof(int));
    memset(node_mapping, -1, n*sizeof(int)); memset(index_mapping, -1, n*sizeof(int)); int lm = 0;
    generate_euler_tour(n, adjlist, root, -1, euler_tour, node_mapping, index_mapping, lm);

    lca result;
    result.first_appear = (int*) malloc(n*sizeof(int));
    memset(result.first_appear, -1, sizeof(int) * n);
    result.node_mapping = node_mapping;
    result.index_mapping = index_mapping;
    result.n = n;
    for (int i = 0; i < (int) euler_tour.size(); i++)
        if (result.first_appear[euler_tour[i]] < 0)
            result.first_appear[euler_tour[i]] = i;
    result.st = generate_sparse_table(euler_tour);
    
    return result;
}

void delete_lca(lca the_lca) {
    delete_sparse_table(the_lca.st);
    free(the_lca.first_appear);
    free(the_lca.node_mapping);
    free(the_lca.index_mapping);
}

int query_lca(const lca& the_lca, int n1, int n2) {
    int a = the_lca.first_appear[the_lca.node_mapping[n1]];
    int b = the_lca.first_appear[the_lca.node_mapping[n2]];
    return the_lca.index_mapping[query_sparse_table(the_lca.st, min(a,b), max(a,b) + 1).second];
}

int n,q;
vector<int> adjlist[1000];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int m,x; scanf("%d", &m);
        while (m--)
            scanf("%d", &x), adjlist[i].push_back(x-1);
    }
    lca l = generate_lca(n, adjlist, 0);
    scanf("%d", &q);
    while (q--) {
        int a,b; scanf("%d%d", &a, &b); a--; b--;
        printf("%d\n", query_lca(l,a,b) + 1);
    }
    delete_lca(l);
    return 0;
}