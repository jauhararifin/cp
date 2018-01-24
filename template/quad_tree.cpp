#include <bits/stdc++.h>

using namespace std;

/**
 * T : node type
 * U : update type
 * joinUpdate : when two update joined
 * updateNode : when node updated using update type
 * joinNode : join node with node
 */
template <typename T, typename U>
class quad_tree {
public:
    quad_tree(int n, T defaultNode, U defaultUpdate, U (*joinUpdate)(U, U), T (*updateNode)(T, U), T (*joinNode)(T, T, T, T)) {
        init(n, NULL, defaultNode, defaultUpdate, joinUpdate, updateNode, joinNode);
    }

    quad_tree(int n, T** arr, T defaultNode, U defaultUpdate, U (*joinUpdate)(U, U), T (*updateNode)(T, U), T (*joinNode)(T, T, T, T)) {
        init(n, arr, defaultNode, defaultUpdate, joinUpdate, updateNode, joinNode);
    }

    void init(int n, T** arr, T defaultNode, U defaultUpdate, U (*joinUpdate)(U, U), T (*updateNode)(T, U), T (*joinNode)(T, T, T, T)) {
        while (__builtin_popcount(n) > 1)
            n += n & -n;

        this->n = n;
        this->defaultNode = defaultNode;
        this->defaultUpdate = defaultUpdate;
        this->joinUpdate = joinUpdate;
        this->updateNode = updateNode;
        this->joinNode = joinNode;

        needUpdate = new bool[6*n*n+1];
        qtree = (T*) malloc((6*n*n+1) * sizeof(T));
        utree = (U*) malloc((6*n*n+1) * sizeof(U));
        for (int i = 0; i < 6*n*n+1; i++)
            needUpdate[i] = 0;
        
        init_quad_tree(1, 0, n-1, 0, n-1, arr);
    }

    ~quad_tree() {
        delete [] needUpdate;
        free(qtree);
        free(utree);
    }

    void update(int left, int right, int top, int bottom, U val) {
        if (right <= left || bottom <= top) return;
        this->left = left;
        this->right = right - 1;
        this->top = top;
        this->bottom = bottom - 1;
        this->val = val;
        rec_update_segtree(1, 0, n - 1, 0, n - 1);
    }

    T query(int left, int right, int top, int bottom) {
        if (right <= left || bottom <= top) return defaultNode;
        this->left = left;
        this->right = right - 1;
        this->top = top;
        this->bottom = bottom - 1;
        return rec_query(1, 0, n - 1, 0, n - 1);
    }

    void debug() {
        rec_debug(1, 0, n-1, 0, n-1, 0);
    }

    int n;
    bool* needUpdate;
    T* qtree;
    U* utree;
    T defaultNode;
    U defaultUpdate;
    U (*joinUpdate)(U, U);
    T (*updateNode)(T, U);
    T (*joinNode)(T, T, T, T);

private:
    void rec_debug(int node, int left, int right, int top, int bottom, int level) {
        if (left > right || top > bottom) return;
        for (int i = 0; i < 4*level; i++) cout<<" ";
        cout<<qtree[node]<<" update: "<<utree[node]<<endl;
        if (left < right || top < bottom) {
            rec_debug(4*node-2, left, (left+right)/2, top, (top+bottom)/2, level+1);
            rec_debug(4*node-1, left, (left+right)/2, (top+bottom)/2+1, bottom, level+1);
            rec_debug(4*node, (left+right)/2+1, right, top, (top+bottom)/2, level+1);
            rec_debug(4*node+1, (left+right)/2+1, right, (top+bottom)/2+1, bottom, level+1);
        }
    }

    T init_quad_tree(int node, int left, int right, int top, int bottom, T** arr) {
        if (left > right || left < 0 || right >= n) return defaultNode;
        if (top > bottom || top < 0 || bottom >= n) return defaultNode;
        if (left == right && top == bottom)
            return qtree[node] = arr != NULL ? arr[top][left] : defaultNode;
        else {
            T a = init_quad_tree(4*node-2, left, (left+right)/2, top, (top+bottom)/2, arr);
            T b = init_quad_tree(4*node-1, left, (left+right)/2, (top+bottom)/2+1, bottom, arr);
            T c = init_quad_tree(4*node, (left+right)/2+1, right, top, (top+bottom)/2, arr);
            T d = init_quad_tree(4*node+1, (left+right)/2+1, right, (top+bottom)/2+1, bottom, arr);
            return qtree[node] = joinNode(a, b, c, d);
        }
    }

    T rec_query(int node, int l, int r, int t, int b) {
        if (node > 6*n*n || r < left || l > right || b < top || t > bottom) return defaultNode;
        
        if (joinUpdate && needUpdate[node]) {
            qtree[node] = updateNode(qtree[node], utree[node]);
            needUpdate[node] = 0;
            if (node*4-2 <= 6*n*n) {
                utree[node*4-2] = needUpdate[node*4-2] ? joinUpdate(utree[node*4-2], utree[node]) : utree[node];
                needUpdate[node*4-2] = 1;
            }
            if (node*4-1 <= 6*n*n) {
                utree[node*4-1] = needUpdate[node*4-1] ? joinUpdate(utree[node*4-1], utree[node]) : utree[node];
                needUpdate[node*4-1] = 1;
            }
            if (node*4 <= 6*n*n) {
                utree[node*4] = needUpdate[node*4] ? joinUpdate(utree[node*4], utree[node]) : utree[node];
                needUpdate[node*4] = 1;
            }
            if (node*4+1 <= 6*n*n) {
                utree[node*4+1] = needUpdate[node*4+1] ? joinUpdate(utree[node*4+1], utree[node]) : utree[node];
                needUpdate[node*4+1] = 1;
            }
        }

        if (l < left || r > right || t < top || b > bottom) {
            T _a = rec_query(4*node-2, l, (l+r)/2, t, (t+b)/2);
            T _b = rec_query(4*node-1, l, (l+r)/2, (t+b)/2+1, b);
            T _c = rec_query(4*node, (l+r)/2+1, r, t, (t+b)/2);
            T _d = rec_query(4*node+1, (l+r)/2+1, r, (t+b)/2+1, b);
            return joinNode(_a,_b,_c,_d);
        } else
            return qtree[node];
    }

    T rec_update_segtree(int node, int l, int r, int t, int b) {
        if (node > 6*n*n) return defaultNode;

        if (joinUpdate && needUpdate[node]) {
            qtree[node] = updateNode(qtree[node], utree[node]);
            needUpdate[node] = 0;
            if (node*4-2 <= 6*n*n) {
                utree[node*4-2] = needUpdate[node*4-2] ? joinUpdate(utree[node*4-2], utree[node]) : utree[node];
                needUpdate[node*4-2] = 1;
            }
            if (node*4-1 <= 6*n*n) {
                utree[node*4-1] = needUpdate[node*4-1] ? joinUpdate(utree[node*4-1], utree[node]) : utree[node];
                needUpdate[node*4-1] = 1;
            }
            if (node*4 <= 6*n*n) {
                utree[node*4] = needUpdate[node*4] ? joinUpdate(utree[node*4], utree[node]) : utree[node];
                needUpdate[node*4] = 1;
            }
            if (node*4+1 <= 6*n*n) {
                utree[node*4+1] = needUpdate[node*4+1] ? joinUpdate(utree[node*4+1], utree[node]) : utree[node];
                needUpdate[node*4+1] = 1;
            }
        }
        
        if (r < left || l > right || b < top || t > bottom) return qtree[node];
        
        if (l < left || r > right || t < top || b > bottom) {
            T _a = rec_update_segtree(4*node-2, l, (l+r)/2, t, (t+b)/2);
            T _b = rec_update_segtree(4*node-1, l, (l+r)/2, (t+b)/2+1, b);
            T _c = rec_update_segtree(4*node, (l+r)/2+1, r, t, (t+b)/2);
            T _d = rec_update_segtree(4*node+1, (l+r)/2+1, r, (t+b)/2+1, b);
            qtree[node] = joinNode(_a,_b,_c,_d);
        } else {
            qtree[node] = updateNode(qtree[node], val);
            if (node*4-2 <= 6*n*n) {
                utree[node*4-2] = needUpdate[node*4-2] ? joinUpdate(utree[node*4-2], val) : val;
                needUpdate[node*4-2] = 1;
            }
            if (node*4-1 <= 6*n*n) {
                utree[node*4-1] = needUpdate[node*4-1] ? joinUpdate(utree[node*4-1], val) : val;
                needUpdate[node*4-1] = 1;
            }
            if (node*4 <= 6*n*n) {
                utree[node*4] = needUpdate[node*4] ? joinUpdate(utree[node*4], val) : val;
                needUpdate[node*4] = 1;
            }
            if (node*4+1 <= 6*n*n) {
                utree[node*4+1] = needUpdate[node*4+1] ? joinUpdate(utree[node*4+1], val) : val;
                needUpdate[node*4+1] = 1;
            }
        }
        return qtree[node];
    }

    int left;
    int right;
    int top;
    int bottom;
    U val;
};

int main() {
    return 0;
}