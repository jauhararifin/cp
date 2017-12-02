#include <bits/stdc++.h>

using namespace std;

int k, p;

long long to_num(int n) {
    long long result = n;
    int tmp = n;
    while (tmp) {
        result = result*10LL + (tmp%10);
        tmp /= 10;
    }
    return result;
}

int main() {
    scanf("%d%d", &k, &p);
    long long sum = 0;
    for (int i = 1; i <= k; i++) {
        sum += to_num(i);
        sum %= p;
    }
    printf("%lld\n", sum % (long long) p);
    return 0;
}