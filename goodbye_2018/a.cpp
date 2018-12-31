#include <bits/stdc++.h>

using namespace std;

int y,b,r;

int main() {
    scanf("%d%d%d", &y, &b, &r);
    r = min(y + 2, min(b + 1, r));
    printf("%d\n", r + r + r - 3);
    return 0;
}