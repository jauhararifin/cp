#include <bits/stdc++.h>
#define i64 long long int
using namespace std;

int n,m,q;
vector<i64> a,b,f;
vector<pair<int,i64> > conn[200000];

template <typename T, typename U>
class segment_tree {
public:
    segment_tree(int n, T defaultNode, U defaultUpdate, U (*joinUpdate)(U, U), T (*updateNode)(T, U), T (*joinNode)(T, T)) {
        vector<T> temp;
        temp.resize(n, defaultNode);
        segment_tree(temp, defaultNode, defaultUpdate, joinUpdate, updateNode, joinNode);
    }

    segment_tree(vector<T> arr, T defaultNode, U defaultUpdate, U (*joinUpdate)(U, U), T (*updateNode)(T, U), T (*joinNode)(T, T)) {
        this->n = arr.size();
        this->defaultNode = defaultNode;
        this->defaultUpdate = defaultUpdate;
        this->joinUpdate = joinUpdate;
        this->updateNode = updateNode;
        this->joinNode = joinNode;

        needUpdate = new bool[4*n+1];
        void* streeP = malloc((4*n+1) * sizeof(T)); stree = (T*) streeP;
        void* utreeP = malloc((4*n+1) * sizeof(U)); utree = (U*) utreeP;
        for (int i = 0; i < 4*n+1; i++) {
            needUpdate[i] = 0;
            memcpy(stree + i, &defaultNode, sizeof(defaultNode));
            memcpy(utree + i, &defaultUpdate, sizeof(defaultUpdate));
        }

        init_segment_tree(1, 0, n-1, arr);
    }

    ~segment_tree() {
        delete [] needUpdate;
        delete [] stree;
        delete [] utree;
    }

    void update(int left, int right, U val) {
        rec_update_segtree(1, left, right-1, 0, n - 1, val);
    }

    T query(int left, int right) {
        return rec_query(1, left, right-1, 0, n - 1);
    }

    void debug() {
        rec_debug(1, 0, n-1, 0);
    }

    int n;
    bool* needUpdate;
    T* stree;
    U* utree;
    T defaultNode;
    U defaultUpdate;
    U (*joinUpdate)(U, U);
    T (*updateNode)(T, U);
    T (*joinNode)(T, T);

private:
    void rec_debug(int node, int left, int right, int level) {
        for (int i = 0; i < 4*level; i++) cout<<" ";
        cout<<stree[node]<<" update: "<<utree[node]<<endl;
        if (left < right) {
            rec_debug(2*node, left, (left+right)/2, level+1);
            rec_debug(2*node+1, (left+right)/2+1, right, level+1);
        }
    }

    T init_segment_tree(int node, int left, int right, vector<T>& arr) {
        if (left > right || left < 0 || right >= n) return defaultNode;
        if (left == right)
            return stree[node] = arr[left];
        else
            return stree[node] = joinNode(init_segment_tree(2*node, left, (left+right)/2, arr), init_segment_tree(2*node+1, (left+right)/2+1, right, arr));
    }

    T rec_query(int node, int left, int right, int l, int r) {
        if (node > 4*n || r < left || l > right) return defaultNode;

        if (joinUpdate && needUpdate[node]) {
            stree[node] = updateNode(stree[node], utree[node]);
            needUpdate[node] = 0;
            if (node*2 <= 4*n) {
                utree[node*2] = needUpdate[node*2] ? joinUpdate(utree[node*2], utree[node]) : utree[node];
                needUpdate[node*2] = 1;
            }
            if (node*2+1 <= 4*n) {
                utree[node*2+1] = needUpdate[node*2+1] ? joinUpdate(utree[node*2+1], utree[node]) : utree[node];
                needUpdate[node*2+1] = 1;
            }
        }

        if (l < left || r > right)
            return joinNode(rec_query(2*node, left, right, l, (l+r)/2), rec_query(2*node+1, left, right, (l+r)/2+1, r));
        else
            return stree[node];
    }

    T rec_update_segtree(int node, int left, int right, int l, int r, U val) {
        if (node > 4*n) return defaultNode;

        if (joinUpdate && needUpdate[node]) {
            stree[node] = updateNode(stree[node], utree[node]);
            needUpdate[node] = 0;
            if (node*2 <= 4*n) {
                utree[node*2] = needUpdate[node*2] ? joinUpdate(utree[node*2], utree[node]) : utree[node];
                needUpdate[node*2] = 1;
            }
            if (node*2+1 <= 4*n) {
                utree[node*2+1] = needUpdate[node*2+1] ? joinUpdate(utree[node*2+1], utree[node]) : utree[node];
                needUpdate[node*2+1] = 1;
            }
        }
        
        if (r < left || l > right) return stree[node];
        
        if (l < left || r > right) {
            stree[node] = joinNode(rec_update_segtree(2*node, left, right, l, (l+r)/2, val), rec_update_segtree(2*node+1, left, right, (l+r)/2+1, r, val));
        } else {
            stree[node] = updateNode(stree[node], val);
            if (node*2 <= 4*n) {
                utree[node*2] = needUpdate[node*2] ? joinUpdate(utree[node*2], val) : val;
                needUpdate[node*2] = 1;
            }
            if (node*2+1 <= 4*n) {
                utree[node*2+1] = needUpdate[node*2+1] ? joinUpdate(utree[node*2+1], val) : val;
                needUpdate[node*2+1] = 1;
            }
        }
        return stree[node];
    }
};

i64 join_update_s1(i64 a, i64 b) { return a + b; }
i64 update_node_s1(i64 a, i64 b) { return a + b; }
i64 join_node_s1(i64 a, i64 b) { if (a < 0) return b; else if (b < 0) return a; return min(a,b); }

int main() {
    scanf("%d%d%d", &n, &m, &q);
    a.push_back(-1); b.push_back(0);
    for (int i = 0; i < n - 1; i++) {
        int x,y; scanf("%d%d", &x, &y);
        a.push_back(x);
        b.push_back(y);
    }
    a.push_back(0); b.push_back(-1);
    for (int i = 0; i < m; i++) {
        int x,y,z; scanf("%d%d%d", &x, &y, &z); x--; y--;
        conn[x].push_back(make_pair(y,z));
    }

    // printf("A:"); for (int i = 0; i < a.size(); i++) printf("% lld", a[i]); printf("\n");
    // printf("B:"); for (int i = 0; i < b.size(); i++) printf("% lld", b[i]); printf("\n");

    segment_tree<i64,i64> stree1(b, -1, 0, join_update_s1, update_node_s1, join_node_s1);
    // stree1.debug();
    for (int i = 1; i <= n; i++) {
        f.push_back(a[i]);
        for (pair<int,i64> v : conn[i-1])
            stree1.update(0, v.first + 1, v.second);
        // printf("================== %d ==================\n", i);
        // stree1.debug();
        f[i-1] += stree1.query(0, n);
        // printf("f(%d) = %lld\n", i, f[i-1]);
    }
    
    segment_tree<i64,i64> stree2(f, -1, 0, join_update_s1, update_node_s1, join_node_s1);
    printf("%lld\n", stree2.query(0, n));
    while (q--) {
        int v; i64 w; scanf("%d%lld", &v, &w);
        stree2.update(v-1,v,w-a[v]);
        a[v] = w;
        printf("%lld\n", stree2.query(0, n));
    }

    return 0;
}