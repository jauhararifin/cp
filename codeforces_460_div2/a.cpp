#include <bits/stdc++.h>

using namespace std;

int n,m;

int main() {
    scanf("%d%d", &n, &m);
    double price = 1000000000000000.00;
    while (n--) {
        int a,b; scanf("%d%d", &a, &b);
        price = min(price, (double)a/(double)b);
    }
    printf("%.9lf\n", price * m);
    return 0;
}