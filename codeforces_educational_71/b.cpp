#include <bits/stdc++.h>

using namespace std;

int n,m,a[50][50],b[50][50];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &a[i][j]);
    memset(b, 0, sizeof b);

    vector<pair<int,int> > v;
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < m-1; j++)
            if (a[i][j] && a[i][j+1] && a[i+1][j] && a[i+1][j+1]) {
                v.push_back({i+1,j+1});
                b[i][j] = b[i][j+1] = b[i+1][j] = b[i+1][j+1] = 1;
            }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (a[i][j] != b[i][j]) {
                printf("-1\n");
                return 0;
            }

    printf("%d\n", (int) v.size());
    for (auto x : v)
        printf("%d %d\n", x.first, x.second);

    return 0;
}

