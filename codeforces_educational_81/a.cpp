#include <bits/stdc++.h>

using namespace std;

int t,n;

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		if (n%2 == 1) {
			printf("7");
			n -= 3;
		}
		for (; n > 0; n -= 2)
			printf("1");
		printf("\n");
	}
	return 0;
}
