#include <bits/stdc++.h>

using namespace std;

int t,n,p[3],bit_min[100002],bit_max[100002];
bool vis[100000];
vector<int> adj[100000],smin[100000],smax[100000];

void euler_tour(int node, int prev, vector<int>& tour) {
    tour.push_back(node);
    for (auto x : adj[node])
        if (x != prev) {
            euler_tour(x, node, tour);
            tour.push_back(node);
        }
}

int read(int* bit, int idx){
    int sum = 0;
    for (;idx > 0; idx -= (idx & -idx))
        sum += bit[idx];
    return sum;
}

void update(int* bit, int idx){
    for (;idx <= n; idx += (idx & -idx))
        bit[idx]++;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        scanf("%d%d%d", p, p + 1, p + 2);
        for (int i = 0; i < n; i++) {
            adj[i].clear(), smin[i].clear(), smax[i].clear();
            bit_min[i+1] = 0;
            bit_max[i+1] = 0;
            vis[i] = 0;
        }
        for (int i = 0; i < n-1; i++) {
            int u,v; scanf("%d%d", &u, &v);
            adj[u-1].push_back(v-1);
            adj[v-1].push_back(u-1);
        }

        vector<int> tour; euler_tour(0, -1, tour);
        for (int x : tour) {
            smin[x].push_back(read(bit_min, x+1));
            if (!vis[x]) update(bit_min, x+2);

            smax[x].push_back(read(bit_max, n-x));
            if (!vis[x]) update(bit_max, n-x+1);

            vis[x] = 1;
        }

        long long h = 0LL;
        for (int i = 0; i < n; i++) {
            vector<int> temp_min;
            int res = i;
            for (int j = 1; j < (int) smin[i].size(); j++) {
                temp_min.push_back(smin[i][j] - smin[i][j-1]);
                res -= smin[i][j] - smin[i][j-1];
            }
            temp_min.push_back(res);
            long long sum_min = 0; for (auto x : temp_min) sum_min += x;

            vector<int> temp_max;
            res = n-i-1;
            for (int j = 1; j < (int) smax[i].size(); j++) {
                temp_max.push_back(smax[i][j] - smax[i][j-1]);
                res -= smax[i][j] - smax[i][j-1];
            }
            temp_max.push_back(res);
            long long sum_max = 0; for (auto x : temp_max) sum_max += x;

            long long hh = 0;
            if (p[1] < p[0] && p[1] < p[2]) {
                for (auto x : temp_max) hh += (long long) x * (long long) (sum_max - x);
                hh = hh / 2;
            } else if (p[1] > p[0] && p[1] > p[2]) {
                for (auto x : temp_min) hh += (long long) x * (long long) (sum_min - x);
                hh = hh / 2;
            } else {
                for (int j = 0; j < (int) temp_min.size(); j++)
                    hh += (long long) temp_min[j] * (long long) (sum_max - temp_max[j]);
            }
            h += hh;
        }

        printf("%lld\n", h);
    }
    return 0;
}