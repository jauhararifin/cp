#include <bits/stdc++.h>

using namespace std;

long long n;

int main() {
	scanf("%lld", &n);
	long long a = 1, b = n;
	for (long long i = 1; i*i < n; i++) {
		if (n % i == 0) {
			long long x = i;
			long long y = n / i;
			if (__gcd(x,y) == 1)
				a = x, b = y;
		}
	}
	printf("%lld %lld\n", a, b);
	return 0;
}
