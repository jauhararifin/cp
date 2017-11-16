#include <bits/stdc++.h>

using namespace std;

bool __folkfulkerson_bpm(int n, int m, int src, vector<int>* adjlist, bool* seen, int* matching) {
	for (int i = 0; i < (int) adjlist[src].size(); i++) {
		int dst = adjlist[src][i];
		if (!seen[dst]) {
			seen[dst] = 1;
			if (matching[dst] < 0 || __folkfulkerson_bpm(n, m, matching[dst], adjlist, seen, matching)) {
				matching[dst] = src;
				return 1;
			}
		}
	}
	return 0;
}

int folkfulkerson_bipartite_matching(int n, int m, vector<int> *adjlist) {
	int* matching = new int[m];
	for (int i = 0; i < m; i++) matching[i] = -1;

	int total = 0;
	for (int i = 0; i < n; i++) {
		bool* seen = new bool[m]; for (int i = 0; i < m; i++) seen[i] = 0;
		if (__folkfulkerson_bpm(n, m, i, adjlist, seen, matching))
			total++;
		delete [] seen;
	}
	delete [] matching;
	return total;
}

int n,m;
tuple<int,int,int> job[150];

bool check(int guess) {
	vector<int>* adjlist = new vector<int>[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i != j && abs(get<0>(job[i]) - get<0>(job[j])) <= guess && get<2>(job[i]) <= get<1>(job[j]))
				adjlist[i].push_back(j);
	int h = n - folkfulkerson_bipartite_matching(n, n, adjlist);
	delete [] adjlist;
	return h <= m;
}	

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%d%d%d", &get<0>(job[i]), &get<1>(job[i]), &get<2>(job[i]));

	int h = -1;
	int lo = 0;
	int hi = 888888888;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		if (check(mid)) {
			h = mid;
			hi = mid - 1;
		} else
			lo = mid + 1;
	}
	printf("%d\n", h);
	return 0;
}