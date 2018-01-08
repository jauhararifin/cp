#include <bits/stdc++.h>

using namespace std;

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

        needUpdate.resize(4*n+1, 0);
        stree.resize(4*n+1, defaultNode);
        utree.resize(4*n+1, defaultUpdate);

        init_segment_tree(1, 0, n-1, arr);
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
    vector<bool> needUpdate;
    vector<T> stree;
    vector<U> utree;
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

bool joinUpdate(bool a, bool b) { return a ^ b; }
pair<int,int> updateNode(pair<int,int> a, bool b) { return b ? make_pair(a.second-a.first, a.second) : a; }
pair<int,int> joinNode(pair<int,int> a, pair<int,int> b) { return make_pair(a.first + b.first, a.second + b.second); }

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int x; scanf("%d", &x); x--;
        adj[x].push_back(i);
    }
    generate_path(0);

    vector<pair<int,int> > tmp; tmp.resize(n,make_pair(0,1));
    segment_tree<pair<int,int>,bool> s(tmp,make_pair(0,0),0, joinUpdate, updateNode, joinNode);;
    for (int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        if (x)
            s.update(pos[i].first, pos[i].first+1, 1);
    }

    scanf("%d", &q);
    while (q--) {
        char ss[4]; int x;
        scanf("%s %d", ss, &x); x--;
        if (ss[0] == 'g')
            printf("%d\n", s.query(pos[x].first, pos[x].second).first);
        else
            s.update(pos[x].first, pos[x].second, 1);
    }

    return 0;
}