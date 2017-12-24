#include <bits/stdc++.h>

using namespace std;

long long n;

int digit(long long x) {
    if (x == 0) return 1;
    int c = 0; while (x) { c++; x /= 10; }
    return c;
}

int num_of_nine(long long x) {
    int c = 0; while (x % 10 == 9) { c++; x /= 10; }
    return c;
}

long long gen_nine(int prefix, int nine) {
    long long result = prefix;
    while (nine--)
        result = 10LL * result + 9;
    return result;
}

int main() {
    scanf("%lld", &n);
    long long temp = n + n - 1;
    int maxn = max(num_of_nine(temp), digit(temp) - 1);

    long long ans = 0;
    for (int i = 0; i < 10; i++) {
        long long target = gen_nine(i, maxn);
        // printf("%lld -> %lld %lld\n", target, target - n, (n - (target - n))/2LL);

        long long lo = 1;
        long long hi = n;
        long long seed = 0;
        while (lo <= hi) {
            long long mid = (lo + hi) / 2;
            long long x = target - mid;
            if (x <= 0)
                hi = mid - 1;
            else {
                lo = mid + 1;
                seed = mid;
            }
        }

        // printf("%lld -> seed: %lld %lld\n", target, seed, target - seed);

        if (seed > target - seed)
            ans += (seed - (target - seed) + 1)/2LL;
    }
    printf("%lld\n", ans);

    return 0;
}