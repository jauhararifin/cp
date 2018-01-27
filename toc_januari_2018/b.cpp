#include <bits/stdc++.h>

using namespace std;

const long long mod = 1000000007LL;
int n, k;
bool special[100000];
vector<int> adj[100000];
long long ans;

// first total
// second not special
pair<long long,long long> solve(int node, int before) {
    if (special[node]) {
        long long t = 1;
        for (int x : adj[node])
            if (x != before)
                t = ((t % mod) * ((1LL + solve(x, node).first) % mod)) % mod;
        ans = (ans + (t % mod)) % mod;
        // printf("%d -> %lld %lld\n", node, t, t);
        return make_pair(t, 0);
    } else {
        long long total = 1LL;
        long long nonspc = 1LL;
        for (int x : adj[node])
            if (x != before) {
                pair<long long,long long> r = solve(x, node);
                total = ((total % mod) * ((1LL + r.first) % mod)) % mod;
                nonspc = ((nonspc % mod) * ((1LL + r.second) % mod)) % mod;
            }
        ans = ((ans + total - nonspc) % mod + mod) % mod;
        return make_pair(total % mod, nonspc % mod);
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n - 1; i++) {
        int x, y; scanf("%d%d", &x, &y); x--; y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    memset(special, 0, sizeof special);
    int x; for (int i = 0; i < k; i++)
        scanf("%d", &x), special[x-1] = 1;
    ans = 0;
    solve(0, -1);
    printf("%lld\n", ans % mod);

    return 0;
}