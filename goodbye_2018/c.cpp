#include <bits/stdc++.h>

using namespace std;

long long n;

int main() {
    scanf("%lld", &n);

    vector<long long> factors;
    for (long long i = 1; i*i <= n; i++)
        if (n % i == 0) {
            factors.push_back(i);
            if (i*i != n)
                factors.push_back(n/i);
        }
    
    set<long long> result;
    for (long long f : factors)
        result.insert((2LL + n - f)*n/(2*f));
    for (long long f : result)
        printf("%lld ", f);
    printf("\n");

    return 0;
}