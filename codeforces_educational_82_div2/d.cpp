#include <bits/stdc++.h>

using namespace std;

int t,m,b[64];
long long n,a[100000];

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%lld%d", &n, &m);
		for (int i = 0; i < m; i++) scanf("%lld", a + i);
		long long sum = 0;
		for (int i = 0; i < m; i++) sum += a[i];
		if (sum < n) {
			printf("-1\n");
			continue;
		}

		memset(b, 0, sizeof b);
		for (int i = 0; i < m; i++)
			for (long long j = 0; j < 63; j++)
				if (a[i] & (1LL<<j)) b[j]++;

		int unhandled = 100;
		int h = 0;
		int saving = 0;
		for (int i = 0; i < 63; i++) {
			if (unhandled < i && saving > 0) {
				saving--;
				unhandled = 100;
			}

			if (unhandled < i && b[i] > 0) {
				h += i - unhandled;
				b[i]--;
				unhandled = 100;
			}

			if (n & (1LL<<i)) unhandled = min(unhandled, i);

			if (unhandled == i && (b[i] + saving) > 0) {
				if (saving > 0) saving--;
				else b[i]--;
				unhandled = 100;
			}

			saving = (saving + b[i]) / 2;
		}
		printf("%d\n", h);
	}
	return 0;
}
