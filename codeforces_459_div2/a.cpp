#include <bits/stdc++.h>

using namespace std;

bool f[1001];

int main() {
    memset(f, 0, sizeof f);
    int a = 1;
    int b = 1;
    while (a <= 1000) {
        f[a] = 1;
        int c = a + b;
        a = b;
        b = c;
    }

    int n; scanf("%d", &n);
    for (int i = 0; i < n; i++)
        if (f[i + 1])
            printf("O");
        else
            printf("o");
    printf("\n");

    return 0;
}