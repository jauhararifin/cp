#include <bits/stdc++.h>

using namespace std;

int n,m;
char f[50][51], a[101];

int main() {
    scanf("%d%d", &n, &m); 
    for (int i = 0; i < n; i++)
        scanf("%s", f[i]);
    scanf("%s", a);

    pair<int,int> start;
    pair<int,int> finish;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (f[i][j] == 'S')
                start = make_pair(i,j);
            else if (f[i][j] == 'E')
                finish = make_pair(i,j);

    int dir[] = {0,1,2,3};
    int ans = 0;
    do {
        pair<int,int> pos = start;
        int na = strlen(a);
        // printf("%d %d %d %d ->", dir[0], dir[1], dir[2], dir[3]);
        for (int i = 0; i < na; i++) {
            // printf(" (%d,%d)", pos.first, pos.second);
            switch(dir[a[i] - '0']) {
                case 0: pos.second++; break;
                case 1: pos.first++; break;
                case 2: pos.first--; break;
                case 3: pos.second--; break;
            }
            if (pos.first < 0 || pos.first >= n || pos.second < 0 || pos.second >= m || f[pos.first][pos.second] == '#') {
                break;
            }
            if (pos == finish) {
                ans++;
                break;
            }
        }
        // printf("\n");
    } while (next_permutation(dir, dir + 4));
    printf("%d\n", ans);

    return 0;
}