#include <bits/stdc++.h>

using namespace std;

int n,pos,l,r;

int main() {
    scanf("%d%d%d%d", &n, &pos, &l, &r);
    if (pos >= l && pos <= r)
        printf("%d\n", min((r < n ? r - pos + 1 : 0) + (l > 1 ? r - l + 1 : 0), 
            (l > 1 ? pos - l + 1 : 0) + (r < n ? r - l + 1 : 0)));
    else if (pos < l)
        printf("%d\n", l - pos + 1 + (r < n ? r - l + 1 : 0));
    else
        printf("%d\n", pos - r + 1 + (l > 1 ? r - l + 1 : 0));

    return 0;
}