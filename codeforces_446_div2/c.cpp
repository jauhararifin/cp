#include <bits/stdc++.h>

using namespace std;

int n,a[2000];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    int minimum = 20000;
    int non_one = 0;
    for (int i = 0; i < n; i++)
        if (a[i] != 1)
            non_one++;
    for (int i = 0; i < n; i++) {
        int gcd = a[i];
        if (a[i] == 1) {
            minimum = 0;
            break;
        }
        int j = i + 1;
        for (; j < n && gcd != 1; j++)
            gcd = __gcd(gcd, a[j]);
        if (gcd == 1)
            minimum = min(minimum, j - i - 1);
    }
    
    if (minimum > n)
        printf("-1\n");
    else if (minimum == 0)
        printf("%d\n", non_one);
    else 
        printf("%d\n", non_one - 1 + minimum);
    return 0;
}