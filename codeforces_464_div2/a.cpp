#include <bits/stdc++.h>

using namespace std;

int n,f[5000];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", f + i), f[i]--;
	for (int i = 0; i < n; i++) {
		int a = i;
		int b = f[i];
		int c = f[b];
		if (f[c] == a) {
			printf("YES\n");
			return 0;
		}
	}
	printf("NO\n");
	return 0;
}