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

int n,m,p;
vector<int> adjlist[50000];

int main() {
	scanf("%d%d%d", &n, &m, &p);
	while (p--) {
		int x,y; scanf("%d%d", &x, &y); x--; y--;
		adjlist[x].push_back(y);
	}
	printf("%d\n", folkfulkerson_bipartite_matching(n,m,adjlist));
}