#include <bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair

using namespace std;

int n,q,c1[600001];
pair<pii,int> qs[300000];

bool needUpdate[2400001];
pii stree[2400001];
bool utree[2400001];
class segment_tree {
public:
    segment_tree(vector<pii>& arr, bool (*joinUpdate)(bool, bool), pii (*updateNode)(pii, bool), pii (*joinNode)(pii, pii)) {
        this->n = arr.size();
        this->defaultNode = make_pair(1,0);
        this->defaultUpdate = 0;
        this->joinUpdate = joinUpdate;
        this->updateNode = updateNode;
        this->joinNode = joinNode;

        memset(needUpdate, 0, sizeof needUpdate);
        memset(utree, 0, sizeof utree);
        
        init_segment_tree(1, 0, n-1, arr);
    }

    void update(int left, int right, bool val) {
        rec_update_segtree(1, left, right-1, 0, n - 1, val);
    }

    pii query(int left, int right) {
        return rec_query(1, left, right-1, 0, n - 1);
    }

    int n;
    pii defaultNode;
    bool defaultUpdate;
    bool (*joinUpdate)(bool, bool);
    pii (*updateNode)(pii, bool);
    pii (*joinNode)(pii, pii);

private:
    pii init_segment_tree(int node, int left, int right, vector<pii>& arr) {
        if (left > right || left < 0 || right >= n) return defaultNode;
        if (left == right)
            return stree[node] = arr[left];
        else
            return stree[node] = joinNode(init_segment_tree(2*node, left, (left+right)/2, arr), init_segment_tree(2*node+1, (left+right)/2+1, right, arr));
    }

    pii rec_query(int node, int left, int right, int l, int r) {
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

    pii rec_update_segtree(int node, int left, int right, int l, int r, bool val) {
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

inline bool join_update(bool a, bool b) { return b; }
inline pii update_node(pii a, bool b) {
    a.first = b ? a.second : 0;
    return a;
}
inline pii join_node(pii a, pii b) { return make_pair(a.first + b.first, a.second + b.second); }

// ostream& operator<<(ostream& os, pair<int,int> a) {
//     os<<"("<<a.first<<","<<a.second<<")"; return os;
// }

int main() {
    ios::sync_with_stdio(0);
    cin>>n>>q;

    vector<int> tomap; tomap.push_back(1); tomap.push_back(n);
    for (int i = 0; i < q; i++) {
        cin>>qs[i].fi.fi>>qs[i].fi.se>>qs[i].se;
        tomap.push_back(qs[i].fi.fi);
        // tomap.insert(qs[i].fi.se);
        if (qs[i].fi.se < n)
            tomap.push_back(qs[i].fi.se + 1);
    }
    sort(tomap.begin(), tomap.end());
    auto tmp = unique(tomap.begin(), tomap.end());
    tomap.resize(distance(tomap.begin(), tmp));

    int cnt = 0, last = 0;
    vector<pii> cmprs;
    for (int x : tomap) {
        c1[cnt++] = x;
        cmprs.push_back(make_pair(1,1));
        if (cmprs.size() > 1)
            cmprs[cmprs.size() - 2] = make_pair(x - last, x - last);
        last = x;
    }

    // printf("c1:"); for (int i = 0; i < cnt; i++)
    //     printf(" %d", c1[i]); printf("\n");

    segment_tree stree(cmprs,join_update, update_node, join_node);
    // stree.debug();
    int m = cnt;
    for (int i = 0; i < q; i++) {
        int l = qs[i].fi.fi, r = qs[i].fi.se, k = qs[i].se;
        int cl = lower_bound(c1, c1 + cnt, l) - c1;
        int cr = lower_bound(c1, c1 + cnt, r + 1) - c1;
        if (c1[cr] != r + 1) cr = m;
        // printf(">> %d %d >> %d %d\n", l, r, cl, cr);
        stree.update(cl, cr, k == 2);
        cout<<stree.query(0, m).first<<"\n";
    }

    return 0;
}