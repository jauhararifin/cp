#include <bits/stdc++.h>

using namespace std;

int n,m,id[300000];
char s[300001];
vector<int> adj[300000];

int memo[300000][26];
int solve(int n, char c) {
    if (memo[n][c-'a'] > -1) return memo[n][c-'a'];
    int h = 0;
    for (int v : adj[n])
        h = max(h, solve(v, c));
    return memo[n][c-'a'] = h + (c == s[n]);
}

int main() {
    scanf("%d%d", &n, &m);
    scanf("%s", s);
    memset(id, 0, sizeof id);
    for (int i = 0; i < m; i++) {
        int x,y; scanf("%d%d", &x, &y); x--; y--;
        adj[x].push_back(y);
        id[y]++;
    }

    queue<int> que;
    for (int i = 0; i < n; i++)
        if (id[i] == 0)
            que.push(i);
    int taken = 0;
    while (!que.empty()) {
        int t = que.front(); que.pop();
        taken++;
        for (int x : adj[t]) if (--id[x] == 0) que.push(x);
    }

    if (taken < n) {
        printf("-1\n");
        return 0;
    }

    memset(memo, -1, sizeof memo);
    int h = 0;
    for (int i = 0; i < n; i++)
        for (char c = 'a'; c <= 'z'; c++)
            h = max(h, solve(i,c));
    printf("%d\n", h);

    return 0;
}