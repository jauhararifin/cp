#include <bits/stdc++.h>

using namespace std;

int n,k,a[500],p[500],c[500];
long long memo[500][500][2];
bool visited[500][500][2];

long long solve(int begin, int end, bool turn) {
	if (visited[begin][end][turn])
		return memo[begin][end][turn];
	if (begin == end)
		return memo[begin][end][turn] = turn ? p[begin] : -p[begin];

	long long take_first = (turn ? p[begin] : -p[begin]) + solve(begin + 1, end, !turn);
	long long take_last = (turn ? p[end] : -p[end]) + solve(begin, end - 1, !turn);
	visited[begin][end][turn] = 1;

	return memo[begin][end][turn] = turn ? max(take_last, take_first) : min(take_last, take_first);
}

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < k; i++)
		scanf("%d", a + i);
	memset(c, 0, sizeof c);
	for (int i = 0; i < n; i++) {
		scanf("%d", p + i);
		p[i]--;
		c[p[i]]++;
	}
	for (int i = 0; i < n; i++)
		p[i] = c[p[i]] * a[p[i]];
	memset(visited, 0, sizeof visited);
	printf("%lld\n", solve(0, n-1, 1));
	return 0;
}

