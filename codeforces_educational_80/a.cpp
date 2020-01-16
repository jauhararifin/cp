#include <bits/stdc++.h>

using namespace std;

int t;
long long n,d;

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%lld%lld", &n, &d);
		
		long long x = d;
		long long lo = 1;
		long long hi = n;
		while (lo <= hi) {
			long long mid = (lo + hi)/2;
			long long r = 0;
			if (mid % 2 == 0)
				r = ((mid + 2) * mid) / 4;
			else
				r = ((mid + 1) * (mid - 1))/4 + (mid+1)/2;
			if (r >= d) {
				x = min(x, mid);
				hi = mid - 1;
			} else
				lo = mid + 1;
		}

		// printf(">>> %lld %lld\n", d, x);

		if (x <= n) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
