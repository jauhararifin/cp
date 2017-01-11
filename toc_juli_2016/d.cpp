#include <bits/stdc++.h>

#define pii pair<int,int>
#define fi first
#define se second

using namespace std;

int n,q,x,y,z,euler[400000],pos[200000];
vector<int> adj[200000];
vector<pair<pii,int> > query;

struct node { int n; node *left, *right; };
node *build_stree(int l, int r) {
	if (l > r) return NULL;
	node* tmp = new node;
	if (l == r) {
		tmp->n = euler[l];
		tmp->left = tmp->right = NULL;
	} else {
		tmp->left = build_stree(l, (l+r)/2);
		tmp->right = build_stree((l+r)/2+1, r);
		tmp->n = min(tmp->left->n, tmp->right->n);
	}
	return tmp;
}
int query_stree(node* root, int left, int right, int l, int r) {
	if (l > r || l > right || r < left) return 2000000000;
	if (l >= left && r <= right) return root->n;
	else return min(query_stree(root->left, left, right, l, (l+r)/2),query_stree(root->right, left, right, (l+r)/2+1, r));
}

int main() {
	scanf("%d", &q);
	n = 1;
	while (q--) {
		scanf("%d", &x);
		if (x == 1) {
			scanf("%d", &x);
			adj[x-1].push_back(n++);
		} else {
			scanf("%d%d%d", &x, &y, &z);
			query.push_back(make_pair(pii(x-1,y-1),z-1));
		}
	}
	stack<int> st;
	st.push(0);
	x = 0;
	while (!st.empty()) {
		int t = st.top(); st.pop();
		euler[x++] = t >= 0 ? t : abs(t)-1;
		if (t >= 0)
			for (int i = (int)adj[t].size()-1; i >= 0; i--)
				st.push(-1-t), st.push(adj[t][i]);
	}
	node* root = build_stree(0, x-1);
	memset(pos, -1, sizeof pos);
	for (int i = 0; i < x; i++)
		if (pos[euler[i]] == -1)
			pos[euler[i]] = i;
			
	for (int i = 0; i < (int) query.size(); i++) {
		int a = query[i].fi.fi, b = query[i].fi.se, c = query[i].se;
		int u = query_stree(root, min(pos[a],pos[b]), max(pos[b],pos[a]), 0, x-1); // a b
		int v = query_stree(root, min(pos[a],pos[c]), max(pos[c],pos[a]), 0, x-1); // a c
		int w = query_stree(root, min(pos[b],pos[c]), max(pos[c],pos[b]), 0, x-1); // b c
		int p = query_stree(root, min(pos[v],pos[b]), max(pos[v],pos[b]), 0, x-1); //(a,c) b
		int q = query_stree(root, min(pos[w],pos[a]), max(pos[w],pos[a]), 0, x-1); //(b,c) a
		
		if ((v == c && u == w) || (w == c && v == u)) printf("%d\n", c+1); // c antara a-b
		else if (u == a && w == b) printf("%d\n", b+1); // c-b-a
		else if (u == b && v == a) printf("%d\n", a+1); // b-a-b
		else if (w == b && u == v) printf("%d\n", b+1); // c-b-*-a
		else if (v == a && u == w) printf("%d\n", a+1); // c-a-*-b
		else if (u == b && p == b) printf("%d\n", v+1);
		else if (u == a && q == a) printf("%d\n", w+1);
		else if (v != u && p == u) printf("%d\n", v+1);
		else if (w != u && q == u) printf("%d\n", w+1);
		else printf("%d\n", u+1);
	}
	return 0;
}
