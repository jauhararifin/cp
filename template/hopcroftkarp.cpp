#include <bits/stdc++.h>

using namespace std;

bool __hopcroftkarp_bfs(int n, int m, vector<int>* adjlist, int *pair_u, int *pair_v, int *dist) {
	queue<int> que;
	for (int i = 0; i < n; i++)
		if (pair_u[i] < 0)
			dist[i] = 0, que.push(i);
		else
			dist[i] = n+m+1;
	dist[-1] = n+m+1;
	while (!que.empty()) {
		int t = que.front(); que.pop();
		if (dist[t] < dist[-1])
			for (int i = 0; i < (int) adjlist[t].size(); i++)
				if (dist[pair_v[adjlist[t][i]]] == n+m+1) {
					dist[pair_v[adjlist[t][i]]] = dist[t] + 1;
					que.push(pair_v[adjlist[t][i]]);
				}
	}
	return dist[-1] != n+m+1;
}

bool __hopcroftkarp_dfs(int n, int m, vector<int>* adjlist, int *pair_u, int *pair_v, int *dist, int node) {
	if (node != -1) {
		for (int i = 0; i < (int) adjlist[node].size(); i++)
			if (dist[pair_v[adjlist[node][i]]] == dist[node] + 1 &&
			    __hopcroftkarp_dfs(n, m, adjlist, pair_u, pair_v, dist, pair_v[adjlist[node][i]])) {
				pair_v[adjlist[node][i]] = node;
				pair_u[node] = adjlist[node][i];
				return 1;
			}
		dist[node] = n+m+1;
		return 0;
	}
	return 1;
} 

int hopcroftkarp(int n, int m, vector<int> *adjlist) {
	int* pair_u = new int[n+1] + 1;
	int* pair_v = new int[m+1] + 1;
	int* dist = new int[n+1] + 1;
	for (int i = -1; i < n; i++)
		pair_u[i] = -1;
	for (int i = -1; i < m; i++)
		pair_v[i] = -1;

	int matching = 0;
	while (__hopcroftkarp_bfs(n, m, adjlist, pair_u, pair_v, dist))
		for (int i = 0; i < n; i++)
			if (pair_u[i] == -1 && __hopcroftkarp_dfs(n, m, adjlist, pair_u, pair_v, dist, i))
				matching++;
	
	delete [] (pair_u-1);
	delete [] (pair_v-1);
	delete [] (dist-1);
	return matching;
}

int n,m,p;
vector<int> adjlist[50000];

int main() {
	scanf("%d%d%d", &n, &m, &p);
	while (p--) {
		int x,y; scanf("%d%d", &x, &y); x--; y--;
		adjlist[x].push_back(y);
	}
	printf("%d\n", hopcroftkarp(n,m,adjlist));
}