#include <bits/stdc++.h>

using namespace std;

bool check(int a) {
    int x = 0;
    while (a) {
        x += a % 10;
        a /= 10;
        if (x > 10) break;
    }
    return x == 10;
}

int n,c,p[10001];

int main() {
    c = 0;
    for (int i = 0; i <= 25000000 && c < 10000; i++)
        if (check(i))
            p[++c] = i;
    scanf("%d", &n);
    printf("%d\n", p[n]);
    return 0;
}