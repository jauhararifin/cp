#include <bits/stdc++.h>

using namespace std;

template <typename T>
T edmonskarp(int n, vector<pair<int,T> >* adj, int s, int t) {
	map<pair<int,int>,T> flow, capacity;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < (int) adj[i].size(); j++)
			capacity[make_pair(i, adj[i][j].first)] += adj[i][j].second;
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
				if (prev[to] < 0 && flow[make_pair(node, to)] < capacity[make_pair(node, to)])
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
			if (aug < 0 || capacity[make_pair(path[i-1], path[i])] - flow[make_pair(path[i-1], path[i])] < aug)
				aug = capacity[make_pair(path[i-1], path[i])] - flow[make_pair(path[i-1], path[i])];
		maxflow += aug;
		for (int i = 1; i < (int) path.size(); i++) {
			flow[make_pair(path[i-1], path[i])] += aug;
			flow[make_pair(path[i], path[i-1])] -= aug;
		}
	}
	delete(prev);

	return maxflow;
}

int n,m;
vector<pair<int,int> > adj[5000];

int main() {
	scanf("%d%d", &n, &m);
	while (m--) {
		int a,b,c; scanf("%d%d%d", &a, &b, &c);
		adj[a-1].push_back(make_pair(b-1,c));
		adj[b-1].push_back(make_pair(a-1,c));
	}
	printf("%d\n", edmonskarp(n, adj, 0, n - 1));
	return 0;
}