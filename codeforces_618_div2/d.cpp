#include <bits/stdc++.h>

using namespace std;

int n,x[100000],y[100000];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d%d", x + i, y + i);

	if (n % 2 == 1) {
		printf("NO\n");
		return 0;
	}

	for (int i = 0; i < n/2; i++) {
		int x1 = x[i+1]-x[i];
		int y1 = y[i+1]-y[i];

		int x2 = x[(i+n/2+1)%n] - x[i+n/2];
		int y2 = y[(i+n/2+1)%n] - y[i+n/2];

		if (x1 != -x2 || y1 != -y2) {
			printf("NO\n");
			return 0;
		}
	}

	printf("YES\n");
	return 0;
}
