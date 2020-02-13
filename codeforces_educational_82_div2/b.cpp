#include <bits/stdc++.h>

using namespace std;

int t;
long long n,g,b;

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%lld%lld%lld", &n, &g, &b);
		long long r = (n + 1) / 2;
		
		long long x = r / g - 1;
		long long good = x > 0 ? x * g : 0;
		long long bad = x > 0 ? x * b : 0;

		// printf("x=%lld, good=%lld, bad=%lld\n", x, good, bad);
		while (good < r) {
			if (good + g >= r) {
				good += r - good;
			} else {
				good += g;
				bad += b;
			}
		}
		
		printf("%lld\n", max(good + bad, n));
	}
	return 0;
}
