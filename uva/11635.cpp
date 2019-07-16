#include <bits/stdc++.h>

using namespace std;

int n,h,m;
pair<int,int> vis[10000];
bool b[10000];
vector<pair<int,int> > adj[10000];

int main() {
    while (1) {
        scanf("%d", &n);
        if (n == 0) return 0;
        scanf("%d", &h);
        memset(b, 0, sizeof b);
        for (int i = 0; i < h; i++) {
            scanf("%d", &m);
            b[m-1] = 1;
        }
        for (int i = 0; i < n; i++) adj[i].clear();
        scanf("%d", &m);
        while (m--) {
            int x,y,z;
            scanf("%d%d%d", &x, &y, &z);
            adj[x-1].push_back({y-1,z});
            adj[y-1].push_back({x-1,z});
        }
        for (int i = 0; i < n; i++)
            vis[i] = {1000000,1000000};

        int h = -1;
        priority_queue<tuple<int,int,int> > pq;
        pq.push({0,0,0});
        while (!pq.empty()) {
            int hot, dist, v;
            tie(hot, dist, v) = pq.top(); pq.pop();
            hot *= -1;
            dist *= -1;
            if (v == n-1) {
                h = hot;
                break;
            }

            if (hot >= vis[v].first && dist >= vis[v].second)
                continue;
            vis[v] = {min(vis[v].first, hot), min(vis[v].second, dist)};

            for (auto next : adj[v]) {
                int next_dist = dist + next.second;
                int next_v = next.first;
                if (next_dist < 600 || (next_dist == 600 && next_v == n-1))
                    pq.push({-hot, -next_dist, next_v});
                if (b[next_v] && next_dist <= 600)
                    pq.push({-hot-1, 0, next_v});
            }
        }

        printf("%d\n", h);
    }
    return 0;
}