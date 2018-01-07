#include <bits/stdc++.h>

using namespace std;

int n;

int main() {
	scanf("%d", &n);
	printf("%d\n", n + n/2);
	for (int i = 2; i <= n; i += 2)
		printf("%d ", i);
	for (int i = 1; i <= n; i += 2)
		printf("%d ", i);
	for (int i = 2; i <= n; i += 2)
		printf("%d ", i);
	printf("\n");
	return 0;
}