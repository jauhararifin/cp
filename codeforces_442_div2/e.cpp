#include <bits/stdc++.h>

using namespace std;

class segment_tree {
public:
    segment_tree(int n) {
        this->n = n;
        stree = new int[4*n+1];
        utree = new bool[4*n+1];
        for (int i = 0; i < 4*n+1; i++)
            stree[i] = utree[i] = 0;
    }

    ~segment_tree() {
        delete [] stree;
        delete [] utree;
    }

    void update(int left, int right) {
        rec_update_segtree(1, left, right-1, 0, n - 1);
    }

    int query(int left, int right) {
        int x = rec_query(1, left, right-1, 0, n - 1);
        return x;
    }

    int n;
    int* stree;
    bool* utree;
private:
    int rec_query(int node, int left, int right, int l, int r) {
        if (node > 4*n || r < left || l > right) return 0;

        if (utree[node]) {
            stree[node] = r - l + 1 - stree[node];
            utree[node] = 0;
            if (node*2 <= 4*n) utree[node*2] ^= 1;
            if (node*2+1 <= 4*n) utree[node*2+1] ^= 1;
        }

        if (l < left || r > right)
            return rec_query(2*node, left, right, l, (l+r)/2) + rec_query(2*node+1, left, right, (l+r)/2+1, r);
        else {
            return stree[node];
        }
    }
    int rec_update_segtree(int node, int left, int right, int l, int r) {
        if (node > 4*n) return 0;

        if (utree[node]) {
            stree[node] = r - l + 1 - stree[node];
            utree[node] = 0;
            if (node*2 <= 4*n) utree[node*2] ^= 1;
            if (node*2+1 <= 4*n) utree[node*2+1] ^= 1;
        }
        
        if (r < left || l > right) return stree[node];
        
        if (l < left || r > right) {
            stree[node] = rec_update_segtree(2*node, left, right, l, (l+r)/2) + rec_update_segtree(2*node+1, left, right, (l+r)/2+1, r);
        } else {
            stree[node] = r - l + 1 - stree[node];
            if (node*2 <= 4*n) utree[node*2] ^= 1;
            if (node*2+1 <= 4*n) utree[node*2+1] ^= 1;
        }
        return stree[node];
    }
};

int n,q;
vector<int> adj[200000],path;
pair<int,int> pos[200000];

int generate_path(int node) {
    int cnt = 1;
    pos[node].first = path.size();
    path.push_back(node);
    for (int x : adj[node])
        cnt += generate_path(x);
    pos[node].second = pos[node].first + cnt;
    return cnt;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int x; scanf("%d", &x); x--;
        adj[x].push_back(i);
    }
    generate_path(0);

    segment_tree s(n);
    for (int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        if (x)
            s.update(pos[i].first, pos[i].first+1);
    }

    scanf("%d", &q);
    while (q--) {
        char ss[4]; int x;
        scanf("%s %d", ss, &x); x--;
        if (ss[0] == 'g')
            printf("%d\n", s.query(pos[x].first, pos[x].second));
        else
            s.update(pos[x].first, pos[x].second);
    }

    return 0;
}