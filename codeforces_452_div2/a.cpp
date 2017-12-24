#include <bits/stdc++.h>

using namespace std;

int n,a,b;

int main() {
    scanf("%d", &n);
    a = b = 0;
    for (int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        if (x == 1) a++;
        else b++;
    }
    printf("%d\n", min(a,b) + (a - min(a,b)) / 3);
    return 0;
}