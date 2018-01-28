#include <bits/stdc++.h>

using namespace std;

int n,m,pos[100000];
bool vpos[100000],v[100000];
vector<pair<int,int> > adj[100000];

bool calc(int node) {
    int mini = 0;
    int maxi = 0;
    pos[node] = 0;
    vpos[node] = 1;
    stack<int> st;
    st.push(node);
    while (!st.empty()) {
        int t = st.top(); st.pop();
        if (v[t]) continue;
        v[t] = 1;
        for (pair<int,int> neig : adj[t]) {
            if (!vpos[neig.first]) {
                pos[neig.first] = pos[t] + neig.second;
                mini = min(mini, pos[neig.first]);
                maxi = max(maxi, pos[neig.first]);
                vpos[neig.first] = 1;
                if (!v[neig.first])
                    st.push(neig.first);
            } else if (pos[neig.first] != neig.second + pos[t])
                return 0;
        }
    }
    return maxi - mini <= 1000000000;
}

int main() {
    scanf("%d%d", &n, &m);
    while (m--) {
        int l,r,d; scanf("%d%d%d", &l, &r, &d); l--; r--;
        adj[l].push_back(make_pair(r,d));
        adj[r].push_back(make_pair(l,-d));
    }
    bool exists = 1;
    memset(vpos, 0, sizeof vpos);
    memset(v, 0, sizeof v);
    for (int i = 0; i < n && exists; i++)
        if (!v[i])
            exists = exists && calc(i);
    printf("%s\n", exists ? "Yes" : "No");

    return 0;
}