#include <bits/stdc++.h>

using namespace std;

int n;
tuple<int,int,int> query[100000];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d%d", &get<0>(query[i]), &get<1>(query[i]), &get<2>(query[i]));
    sort(query, query + n);

    int t = 0, x = 0, y = 0;
    bool can = 1;
    for (int i = 0; i < n && can; i++) {
        int a,b,c; tie(a,b,c) = query[i];
        int dist = abs(b - x) + abs(c - y);
        if (dist > a - t)
            can = 0;
        else
            can = ((a - t) - dist) % 2 == 0;
    }
    if (can) printf("Yes\n");
    else printf("No\n");

    return 0;
}