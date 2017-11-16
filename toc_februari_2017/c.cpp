#include <bits/stdc++.h>

using namespace std;

const int mod = 1000000007;

int n,a[100000],bit[100001];

int compress(int n, int* a) {
	set<int> compress_set;
	for (int i = 0; i < n; i++)
		compress_set.insert(a[i]);
	unordered_map<int,int> compress_map;
	int index = 0;
	for (int x : compress_set)
		compress_map[x] = ++index;
	for (int i = 0; i < n; i++)
		a[i] = compress_map[a[i]];
	return index;
}

int query(int *bit, int idx) {
    int sum = 0;
    for (; idx > 0; idx -= (idx & -idx))
        sum = ((sum % mod) + (bit[idx] % mod)) % mod;
    return sum;
}

void update(int *bit, int n, int idx ,int val) {
    for (; idx <= n; idx += (idx & -idx))
        bit[idx] = ((bit[idx] % mod) + val % mod) % mod;
}

int pow(int a, int b) {
	if (b == 0) return 1;
	if (b == 1) return a % mod;
	int c = pow(a, b/2) % mod;
	if (b & 1) return (((long long) a) * (((long long)c*(long long)c) % mod)) % mod;
	return ((long long)c*(long long)c) % mod;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", a + i);
	int max_num = compress(n, a);

	// calculate ascending
	int result = 0;
	memset(bit, 0, sizeof bit);
	for (int i = 0; i < n; i++)
		update(bit, max_num, a[i], query(bit, a[i]) + 1);
	// printf("ascending: %d\n", query(bit, max_num));
	result += query(bit, max_num);

	// calculate descending
	memset(bit, 0, sizeof bit);
	for (int i = n-1; i >= 0; i--)
		update(bit, max_num, a[i], query(bit, a[i]) + 1);
	// printf("descending: %d\n", query(bit, max_num));
	result = (result + query(bit, max_num)) % mod;

	// calculate both
	map<int,int> count;
	for (int i = 0; i < n; i++)
		count[a[i]]++;
	for (auto it = count.begin(); it != count.end(); it++)
		result = ((((result % mod) - ((pow(2,it->second)-1) % mod)) % mod) + mod) % mod;

	printf("%d\n", ((((pow(2,n) - 1) - result) % mod) + mod) % mod);
	return 0;
}