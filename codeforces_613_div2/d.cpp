#include <bits/stdc++.h>

using namespace std;

int n,a[100000];

int get_min(int lo, int hi, int bit) {
	if (bit < 0) return 0;
	int mask = 1 << bit;
	int f = lo;
	for (int i = lo; i < hi; i++)
		if (a[i] & mask) {
			f = i;
			break;
		}
	if (f == lo) return get_min(lo, hi, bit - 1);
	return mask | min(get_min(lo, f, bit-1), get_min(f, hi, bit-1));
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", a + i);
	sort(a, a + n);
	printf("%d\n", get_min(0, n, 30));
	return 0;
}
