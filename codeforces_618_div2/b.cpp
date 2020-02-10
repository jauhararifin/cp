#include <bits/stdc++.h>

using namespace std;

int t,n,a[200000];

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < 2*n; i++) scanf("%d", a + i);
		sort(a, a + 2*n);
		printf("%d\n", abs(a[n-1]-a[n]));
	}
	return 0;
}
