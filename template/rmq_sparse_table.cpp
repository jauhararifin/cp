#include <bits/stdc++.h>

using namespace std;

template<typename T>
class sparse_table {
public:
    sparse_table(const vector<T>& arr, T (*merge)(T,T)) {
        n = (int) arr.size();
        this->merge = merge;
        fill_sparse_table(arr.data());
    }

    sparse_table(int n, const T* arr, T (*merge)(T,T)) {
        this->n = n;
        this->merge = merge;
        fill_sparse_table(arr);
    }

    ~sparse_table() {
        for (int i = 0; i < n; i++)
            free(st[i]);
        delete [] st;
    }

    // pair<index,value>, query on [from,to)
    T query(int from, int to) {
        to--;
        int k = (int) log2(to-from+1);
        T _a = st[from][k];
        T _b = st[to-(1<<k)+1][k];
        return merge(_a, _b);
    }

    int n;
    T** st;
    T (*merge)(T,T);
private:
    void fill_sparse_table(const T* arr) {
        st = new T*[n];
        for (int i = 0; i < n; i++) {
            st[i] =  (T*) malloc((log2(n-i)+1) * sizeof(T));
            st[i][0] = arr[i];
        }

        for (int j = 1; (1<<j) <= n; j++)
            for (int i = 0; i + (1<<j) - 1 < n; i++) {
                T _a = st[i][j-1];
                T _b = st[i+(1<<(j-1))][j-1];
                st[i][j] = merge(_a, _b);
            }
    }
};

int n,a[100000],q,x,y;

int cmp(int a, int b) { return min(a,b); }

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", a + i);
    sparse_table<int> st(n, a, cmp);

    scanf("%d", &q);
    while (q--) {
        scanf("%d%d", &x, &y);
        printf("%d\n", st.query(x, y + 1));
    }

    return 0;
}