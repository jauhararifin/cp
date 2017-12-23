#include <bits/stdc++.h>

using namespace std;

int a,b,c,d;

int main() {
	scanf("%d%d%d%d", &a, &b, &c, &d);
	for (int i = 0; i <= 201; i++)
		for (int j = 0; j < i; j++)
			for (int k = 0; k < j; k++)
				if (a <= i && 2*a >= i && b <= j && 2*b >= j && c <= k && 2*c >= k && 
					d <= i && d <= j && d <= k && 2*d < i && 2*d < j && 2*d >= k) {
					printf("%d\n%d\n%d\n", i, j, k);
					return 0;
				}
	printf("-1\n");
	return 0;
}