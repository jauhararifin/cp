#include <bits/stdc++.h>

using namespace std;

inline int joinNode(int a, int b) {
    if (a < 0) a = b;
    if (b < 0) b = a;
    return __gcd(a,b);
}
int stree[2000001],utree[2000001];
class segment_tree {
public:
    segment_tree(int n, int* arr) {
        this->n = n;
        this->defaultNode = -1;
        init_segment_tree(1, 0, n-1, arr);
    }

    void update(int left, int val) {
        rec_update_segtree(1, left, 0, n - 1, val);
    }

    int query(int left, int right, int x) {
        return rec_query(1, left, right-1, 0, n - 1, x);
    }

    int n;
    int defaultNode;

private:
    int init_segment_tree(int node, int left, int right, int* arr) {
        if (left > right || left < 0 || right >= n) return defaultNode;
        if (left == right)
            return stree[node] = arr[left];
        else
            return stree[node] = joinNode(init_segment_tree(2*node, left, (left+right)/2, arr), init_segment_tree(2*node+1, (left+right)/2+1, right, arr));
    }

    int rec_query(int node, int left, int right, int l, int r, int x) {
        if (node > 4*n || r < left || l > right) return 0;

        if (l < left || r > right) {
            return rec_query(2*node, left, right, l, (l+r)/2, x) + rec_query(2*node+1, left, right, (l+r)/2+1, r, x);
        } else {
            if (stree[node] % x == 0)
                return 0;
            else if (l == r)
                return 1;
            else {
                int a = rec_query(2*node, left, right, l, (l+r)/2, x);
                if (a > 1) return a;
                int b = rec_query(2*node+1, left, right, (l+r)/2+1, r, x);
                return a + b;
            }
        }
    }

    int rec_update_segtree(int node, int pos, int l, int r, int val) {
        if (node > 4*n) return defaultNode;
        if (r < pos || l > pos) return stree[node];
        if (l < r)
            stree[node] = joinNode(rec_update_segtree(2*node, pos, l, (l+r)/2, val), rec_update_segtree(2*node+1, pos, (l+r)/2+1, r, val));
        else
            stree[node] = val;
        return stree[node];
    }
};

int n,q,v[500000];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", v + i);

    segment_tree stree(n, v);
    scanf("%d", &q);
    while (q--) {
        int a,b,c,d; scanf("%d%d%d",&a,&b,&c);
        if (a == 1) {
            scanf("%d", &d);
            int l = b - 1, r = c - 1;

            if (stree.query(l, r + 1, d) <= 1)
                printf("YES\n");
            else
                printf("NO\n");
        } else {
            stree.update(b - 1, c);
        }
    }

    return 0;
}