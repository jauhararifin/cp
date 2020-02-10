#include <bits/stdc++.h>

using namespace std;

int n,a[100000],b[30];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", a + i);

	memset(b, 0, sizeof b);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 30; j++)
			if (a[i] & (1<<j)) b[j]++;

	int ma = -1;
	int pos = -1;
	for (int i = 0; i < n; i++) {
		int minus = 0;
		for (int j = 0; j < 30; j++) {
			int x = b[j];
			if (a[i] & (1<<j)) x--;
			if (x > 0) minus |= 1<<j;
		}

		int v = (a[i]|minus) - minus;
		if (v > ma) {
			ma = v;
			pos = i;
		}
	}

	printf("%d", a[pos]);
	for (int i = 0; i < n; i++)
		if (i != pos)
			printf(" %d", a[i]);
	printf("\n");

	return 0;
}
