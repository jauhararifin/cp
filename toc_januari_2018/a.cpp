#include <bits/stdc++.h>

using namespace std;

int n, v[22361];

int main() {
    int cv = 0;
    for (int i = 1, j = 0; i <= 1000000000; j += 4, i += j)
        v[cv++] = i;

    scanf("%d", &n);
    int level = upper_bound(v, v + cv, n) - v;
    int last = v[level - 1];

    if (n - last == 0)
        printf("%d %d\n", 0, -level + 1);
    else if (n-last <= level*2-1)
        printf("%d %d\n", -level + (n-last)/2, (n-last)/2 * ((n-last) % 2 ? -1 : 1));
    else if (n-last <= level*3-1) {
        int rem = n - last - (level*2 - 1);
        printf("%d %d\n", rem - 1, level - rem + 1);
    } else {
        int rem = n - last - (level*2 - 1) - level;
        printf("%d %d\n", level - rem + 1, -rem + 1);
    }

    return 0;
}