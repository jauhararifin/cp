#include <bits/stdc++.h>

using namespace std;

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

int n,a[100000],q,x,y;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", a + i);
    rmq::sparse_table<int> st = rmq::generate_sparse_table(n, a);

    scanf("%d", &q);
    while (q--) {
        scanf("%d%d", &x, &y);
        printf("%d\n", rmq::query_sparse_table(st, x, y + 1).second);
    }

    rmq::delete_sparse_table(st);
    return 0;
}