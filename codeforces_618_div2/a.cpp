#include <bits/stdc++.h>

using namespace std;

int t,n,a[100];

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%d", a + i);
		
		int zeros = 0;
		for (int i = 0; i < n; i++)
			if (a[i] == 0)
				zeros++;

		int sum = 0;
		for (int i = 0; i < n; i++)
			sum += a[i];

		if (zeros == 0) {
			printf("%d\n", sum == 0 ? 1 : 0);
		} else {
			if ((sum + zeros) == 0) printf("%d\n", zeros + 1);
			else printf("%d\n", zeros);
		}
	}
	return 0;
}
