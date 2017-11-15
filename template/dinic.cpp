#include <bits/stdc++.h>

using namespace std;

template<typename T>
T dinic_flow(vector<pair<int,T> >* adjlist, int* level, T** flow, T** capacity, int s, int t, T aug) {
	if (aug == 0 || s == t) return aug;
	T total_flow = 0;
	for (int i = 0; aug != 0 && i < (int) adjlist[s].size(); i++) {
		pair<int,T> edge = adjlist[s][i];
		if (level[s] + 1 == level[edge.first]) {
			T new_aug = capacity[s][edge.first] - flow[s][edge.first];
			T new_flow = dinic_flow(adjlist, level, flow, capacity, edge.first, t, aug < 0 ? new_aug : min(aug, new_aug));
			total_flow += new_flow;
			flow[s][edge.first] += new_flow;
			flow[edge.first][s] -= new_flow;
			aug -= new_flow;
		}
	}
	return total_flow;
}

template<typename T>
T dinic(int n, vector<pair<int,T> >* adjlist, int s, int t) {
	T maxflow = 0;

	T** flow = new T*[n];
	T** capacity = new T*[n];
	vector<int> *adj = new vector<int>[n];
	for (int i = 0; i < n; i++) {
		flow[i] = new T[n];
		capacity[i] = new T[n];
		for (int j = 0; j < n; j++)
			flow[i][j] = 0, capacity[i][j] = 0;
		for (int j = 0; j < (int) adjlist[i].size(); j++) {
			if (capacity[i][adjlist[i][j].first] == 0)
				adj[i].push_back(adjlist[i][j].first);
			capacity[i][adjlist[i][j].first] += adjlist[i][j].second;
		}
	}
	int* level = new int[n];

	while (1) {
		for (int i = 0; i < n; i++) level[i] = -1;
		level[s] = 0;
		queue<int> que; que.push(s);
		while (!que.empty()) {
			int t = que.front(); que.pop();
			for (int i = 0; i < (int) adj[t].size(); i++) {
				int next = adj[t][i];
				if (level[next] < 0 && flow[t][next] < capacity[t][next]) {
					level[next] = level[t] + 1;
					que.push(next);
				}
			}
		}
		if (level[t] < 0)
			break;
		T new_flow;
		while (new_flow = dinic_flow(adjlist, level, flow, capacity, s, t, (T) -1))
			maxflow += new_flow;
	}
	
	for (int i = 0; i < n; i++)
		delete [] flow[i], delete [] capacity[i];
	delete [] adj;
	delete [] flow;
	delete [] capacity;
	delete [] level;

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
	printf("%lld\n", dinic(n, adj, 0, n - 1));
	return 0;
}