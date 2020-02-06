#include <bits/stdc++.h>

using namespace std;

int t,n,a[300000];

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%d", a + i);

		int lo = -1;
		for (int i = 0; i < n && a[i] >= i; i++, lo++);

		int hi = n;
		for (int i = 0; i < n && a[n-1-i] >= i; i++, hi--);

		// printf("lo=%d, hi=%d\n", lo, hi);
		if (lo < hi) printf("No\n");
		else printf("Yes\n");
	}
	return 0;
}
