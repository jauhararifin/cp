#include <bits/stdc++.h>

using namespace std;

int T;
long long a,m;

long long gcd(long long a, long long b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

bool isprime(long long x) {
	for (long long i = 2; i*i <= x; i++)
		if (x % i == 0)
			return 0;
	return 1;
}

long long tot(long long p, long long below) {
	long long h = below;
	for (long long i = 1; i*i <= p; i++) {
		if (p % i != 0) continue;
		if (i != 1 && isprime(i)) h = (h / i) * (i - 1);
		if (p != i && i*i != p && isprime(p/i)) h = (h / (p/i)) * ((p/i) - 1);
	}
	// printf("tot %lld %lld -> %lld\n", p, below, h);
	return h;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld", &a, &m);
		long long G = gcd(a,m);
		long long k = m / G;
		long long l = a / G;
		printf("%lld\n", tot(k, l + k) - tot(k, l));
	}
	return 0;
}
