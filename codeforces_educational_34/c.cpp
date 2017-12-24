#include <bits/stdc++.h>

using namespace std;

int n;
map<int,int> m;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        m[x]++;
    }
    int res = -1;
    for (map<int,int>::iterator i = m.begin(); i != m.end(); i++)
        if (i->second > res)
            res = i->second;
    printf("%d\n", res);
    return 0;
}