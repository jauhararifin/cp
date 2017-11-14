#include <bits/stdc++.h>

using namespace std;

template <typename T>
T edmonskarp(int n, vector<pair<int,T> >* adj, int s, int t) {
	T** flow = new T*[n];
	T** capacity = new T*[n];
	for (int i = 0; i < n; i++) {
		flow[i] = new T[n];
		capacity[i] = new T[n];
		for (int j = 0; j < n; j++)
			flow[i][j] = capacity[i][j] = 0;
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < (int) adj[i].size(); j++)
			capacity[i][adj[i][j].first] += adj[i][j].second;
	T maxflow = 0;
	
	int* prev = new int[n];
	while (1) {
		for (int i = 0; i < n; i++) prev[i] = -1;
		queue<pair<int,int> > que; que.push(make_pair(s,s));
		while (!que.empty()) {
			pair<int,int> x = que.front(); que.pop();
			int node = x.first;
			int node_prev = x.second;
			if (prev[node] > -1) continue;
			prev[node] = node_prev;
			if (node == t) break;
			for (int i = 0; i < (int) adj[node].size(); i++) {
				int to = adj[node][i].first;
				if (prev[to] < 0 && flow[node][to] < capacity[node][to])
					que.push(make_pair(to, node));
			}
		}
		if (prev[t] < 0) break;

		vector<int> path;
		int cur = t;
		while (cur != prev[cur])
			path.push_back(cur), cur = prev[cur];
		path.push_back(s);
		reverse(path.begin(), path.end());

		T aug = -1;
		for (int i = 1; i < (int) path.size(); i++)
			if (aug < 0 || capacity[path[i-1]][path[i]] - flow[path[i-1]][path[i]] < aug)
				aug = capacity[path[i-1]][path[i]] - flow[path[i-1]][path[i]];
		maxflow += aug;
		for (int i = 1; i < (int) path.size(); i++) {
			flow[path[i-1]][path[i]] += aug;
			flow[path[i]][path[i-1]] -= aug;
		}
	}
	delete(prev);
	for (int i = 0; i < n; i++)
		delete(flow[i]), delete(capacity[i]);
	delete(flow); delete(capacity);

	return maxflow;
}

int n,m;
vector<pair<int,long long> > adj[5000];

int main() {
	scanf("%d%d", &n, &m);
	while (m--) {
		int a,b; long long c; scanf("%d%d%lld", &a, &b, &c);
		adj[a-1].push_back(make_pair(b-1,c));
		adj[b-1].push_back(make_pair(a-1,c));
	}
	printf("%lld\n", edmonskarp(n, adj, 0, n - 1));
	return 0;
}