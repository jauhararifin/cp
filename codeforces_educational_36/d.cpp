#include <bits/stdc++.h>

using namespace std;

int n,m,id[500];
vector<int> adj[500];

unordered_set<int> st;
pair<int,int> dfs(int node) {
    st.insert(node);
    for (int v : adj[node])
        if (st.find(v) == st.end()) {
            pair<int,int> r = dfs(v);
            if (r.first > -1)
                return r;
        } else
            return make_pair(node, v);
    st.erase(node);
    return make_pair(-1, -1);
}

int tid[500];
bool toposort(int start, int n) {
    memcpy(tid, id, sizeof id);
    queue<int> q; q.push(start); tid[start] = 0;
    while (!q.empty()) {
        int t = q.front(); q.pop(); n--;
        for (int v : adj[t])
            if (--tid[v] == 0)
                q.push(v);
    }
    return n <= 0;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int x,y; scanf("%d%d", &x, &y); x--; y--;
        adj[x].push_back(y);
        id[y]++;
    }

    queue<int> q;
    for (int i = 0; i < n; i++)
        if (id[i] == 0)
            q.push(i);
    int cnt = n;
    while (!q.empty()) {
        int t = q.front(); q.pop();
        cnt--;
        for (int v : adj[t])
            if (--id[v] == 0)
                q.push(v);
    }
    if (cnt == 0) {
        printf("YES\n");
        return 0;
    }
    for (int i = 0; i < n; i++)
        if (id[i] == 1 && toposort(i, cnt)) {
            printf("YES\n");
            return 0;
        }
    printf("NO\n");

    return 0;
}