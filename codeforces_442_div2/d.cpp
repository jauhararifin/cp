#include <bits/stdc++.h>

using namespace std;

int n,m,k,_x1,_y1,_x2,_y2;
char p[1000][1001];
int adj[1000000][4];
bool inque[1000000];

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; i++)
        scanf("%s", p[i]);
    scanf("%d%d%d%d", &_y1, &_x1, &_y2, &_x2); _x1--; _y1--; _x2--; _y2--;

    for (int i = 0; i < n; i++) {
        int l = 0;
        for (int j = 0; j < m; j++)
            if (p[i][j] == '.')
                adj[i*m+j][0] = max(0, max(l, j - k)); // left
            else
                l = j + 1;
        l = m - 1;
        for (int j = m - 1; j >= 0; j--)
            if (p[i][j] == '.')
                adj[i*m+j][1] = min(m-1, min(l, j + k)); // right
            else
                l = j - 1;
    }
    for (int j = 0; j < m; j++) {
        int l = 0;
        for (int i = 0; i < n; i++)
            if (p[i][j] == '.')
                adj[i*m+j][2] = max(0, max(l, i - k)); // top
            else
                l = i + 1;
        l = n - 1;
        for (int i = n - 1; i >= 0; i--)
            if (p[i][j] == '.')
                adj[i*m+j][3] = min(n-1, min(l, i + k)); // bottom
            else
                l = i - 1;
    }

    // for (int i = 0; i < n*m; i++) {
    //     printf("%d ->", i);
    //     for (int x : adj[i])
    //         printf(" %d", x);
    //     printf("\n");
    // }

    memset(inque, 0, sizeof inque);
    queue<pair<int,int> > que; que.push(make_pair(_y1*m + _x1,0));
    while (!que.empty()) {
        pair<int,int> t = que.front(); que.pop();
        int pos = t.first, step = t.second;
        // printf(">> %d %d\n", pos, step);

        if (pos == _y2*m + _x2) { printf("%d\n", step); return 0; }
        int row = pos / m, col = pos % m;
        for (int i = adj[pos][0]; i <= adj[pos][1]; i++)
            if (!inque[row * m + i]) {
                que.push(make_pair(row * m + i, step + 1));
                inque[row * m + i] = 1;
            }
        for (int i = adj[pos][2]; i <= adj[pos][3]; i++)
            if (!inque[i * m + col]) {
                que.push(make_pair(i * m + col, step + 1));
                inque[i * m + col] = 1;
            }
    }
    printf("-1\n");

    return 0;
}