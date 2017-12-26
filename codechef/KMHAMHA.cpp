#include <bits/stdc++.h>

using namespace std;

template<typename T>
T dinic_flow(unordered_set<int>* adjlist, int* level, T** flow, T** capacity, int s, int t, T aug) {
    if (aug == 0 || s == t) return aug;
	T total_flow = 0;
    for (unordered_set<int>::iterator i = adjlist[s].begin(); aug != 0 && i != adjlist[s].end(); i++) {
        int next = *i;
		if (level[s] + 1 == level[next]) {
			T new_aug = capacity[s][next] - flow[s][next];
			T new_flow = dinic_flow(adjlist, level, flow, capacity, next, t, aug < 0 ? new_aug : min(aug, new_aug));
			total_flow += new_flow;
			flow[s][next] += new_flow;
			flow[next][s] -= new_flow;
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
	unordered_set<int> *adj = new unordered_set<int>[n];
	for (int i = 0; i < n; i++) {
		flow[i] = new T[n];
		capacity[i] = new T[n];
		for (int j = 0; j < n; j++)
			flow[i][j] = 0, capacity[i][j] = 0;
		for (int j = 0; j < (int) adjlist[i].size(); j++) {
            adj[i].insert(adjlist[i][j].first);
            adj[adjlist[i][j].first].insert(i);
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
            for (unordered_set<int>::iterator it = adj[t].begin(); it != adj[t].end(); it++) {
				int next = *it;
				if (level[next] < 0 && flow[t][next] < capacity[t][next]) {
					level[next] = level[t] + 1;
					que.push(next);
				}
			}
		}
		if (level[t] < 0)
			break;
		T new_flow;
		while ((new_flow = dinic_flow(adj, level, flow, capacity, s, t, (T) -1)) > 0)
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

int t, n;
pair<int,int> p[1000];
map<int,int> xmap, ymap;
vector<pair<int,int> > adjlist[3002];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d%d", &p[i].first, &p[i].second);

        xmap.clear();
        ymap.clear();
        int nx = 0, ny = 0;
        for (int i = 0; i < n; i++) {
            if (xmap.find(p[i].first) == xmap.end())
                xmap[p[i].first] = nx++;
            if (ymap.find(p[i].second) == ymap.end())
                ymap[p[i].second] = ny++;
        }
        
        for (int i = 0; i < nx + ny + 2; i++)
            adjlist[i].clear();
        for (int i = 0; i < n; i++)
            adjlist[xmap[p[i].first]].push_back(make_pair(nx + ymap[p[i].second], 1));
        for (int i = 0; i < nx; i++)
            adjlist[nx + ny].push_back(make_pair(i,1));
        for (int i = 0; i < ny; i++)
            adjlist[nx + i].push_back(make_pair(nx + ny + 1, 1));

        printf("%d\n", dinic(nx + ny + 2, adjlist, nx + ny, nx + ny + 1));
    }
    return 0;
}