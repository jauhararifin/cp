#include <bits/stdc++.h>

using namespace std;

int n,m,k;
char s[2000][2001];

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; i++)
        scanf("%s", s + i);

    int h = 0;
    for (int j = 0; j < m; j++) {
        int c = 0;
        for (int i = 0; i < n; i++) {
            if (s[i][j] == '.')
                c++;
            else
                c = 0;
            if (c >= k) {
                h++;
                if (k == 1)
                    s[i][j] = '*';
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int c = 0;
        for (int j = 0; j < m; j++) {
            if (s[i][j] == '.')
                c++;
            else
                c = 0;
            if (c >= k)
                h++;
        }
    }

    printf("%d\n", h);

    return 0;
}