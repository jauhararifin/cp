#include <bits/stdc++.h>

using namespace std;

int n;
long long a[100000];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lld", a + i);
    sort(a + 1, a + n);
    long long hp = a[0];
    bool menang = 1;
    for (int i = 1; i < n && menang; i++) {
        if (hp < a[i]) menang = 0;
        hp = abs(hp - a[i]);
    }
    if (menang) {
        printf("menang\n");
        for (int i = 0; i < n - 1; i++)
            printf("%d ", a[i]);
        printf("%d\n", a[n-1]);
    } else
        printf("kalah\n");
    return 0;
}