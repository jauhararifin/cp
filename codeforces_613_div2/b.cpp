#include <bits/stdc++.h>

using namespace std;

int t,n;
long long a[100000],p[100000];

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%lld", a + i);
		p[0] = 0;
		for (int i = 1; i < n; i++) p[i] = p[i-1] + a[i-1];
		
		long long mi = 1000000000000000LL;
		long long ma = -1000000000000000LL;
		long long s = 0;
		for (int i = 0; i < n-1; i++) {
			s = s + a[i];
			mi = min(mi, p[i]);
			ma = max(ma, s - mi);
			// printf(">>> %lld %lld %lld\n", s, mi, ma);
		}
		s += a[n-1];
		for (int i = n-1; i > 0; i--) {
			// printf("%d -> %lld %lld\n", i, s, p[i]);
			ma = max(ma, s - p[i]);
		}
		// printf("s=%lld ma=%lld\n", s, ma);
		if (s > ma) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
