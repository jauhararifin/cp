#include <bits/stdc++.h>

using namespace std;

int i, j, r, c;

int main() {
	scanf("%d%d", &r, &c);
	int n = r * c;
	i = 0;
	j = r * c - 1;
	while (n--) {
		int x; scanf("%d", &x);
		if (x == 1 || x == 3) {
			printf("%d %d\n", i/c + 1, i % c + 1);
			i++;
		} else {
			printf("%d %d\n", j/c + 1, j % c + 1);
			j--;
		}
		fflush(stdout);
	}
	return 0;
}

