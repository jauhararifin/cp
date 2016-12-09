#include <bits/stdc++.h>

#define pii pair<int,int>
#define fi first
#define se second
#define vi vector<int>
#define vii vector<pii>

using namespace std;

typedef struct tstree {
	vi arr;
	struct tstree *left, *right;
} stree;

int n,p[100000],q,l,r;
set<pii> s;

stree* generate_seg_tree(int xl, int xr) {
	if (xl > xr) return NULL;
	if (xl == xr) {
		stree* tmp = new stree;
		tmp->arr = vi();
		for (set<pii>::iterator i = s.lower_bound(pii(xl,-1)); i != s.end() && i->fi == xl; i++)
			tmp->arr.push_back(i->se);
		tmp->left = tmp->right = NULL;
		return tmp;
	}
	stree *left = generate_seg_tree(xl, (xl + xr)/2);
	stree *right = generate_seg_tree((xl + xr)/2 + 1, xr);
	stree* tmp = new stree;
	tmp->arr = vi();
	int i=0,j=0;
	while (i < (int) left->arr.size() && j < (int) right->arr.size())
		if (left->arr[i] < right->arr[j])
			tmp->arr.push_back(left->arr[i++]);
		else
			tmp->arr.push_back(right->arr[j++]);
	while (i < (int) left->arr.size()) tmp->arr.push_back(left->arr[i++]);
	while (j < (int) right->arr.size()) tmp->arr.push_back(right->arr[j++]);
	tmp->left = left;
	tmp->right = right;
	return tmp;
}

int query_seg_tree(stree* node, int xl, int xr, int yl, int yr, int cxl, int cxr) {
	if (node == NULL || cxr < xl || cxl > xr) return 0;
	if (cxl >= xl && cxr <= xr)
		return upper_bound(node->arr.begin(), node->arr.end(), yr) - lower_bound(node->arr.begin(), node->arr.end(), yl);
	return query_seg_tree(node->left, xl, xr, yl, yr, cxl, (cxl+cxr)/2) + query_seg_tree(node->right, xl, xr, yl, yr, (cxl+cxr)/2+1, cxr);
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", p + i);
		
	stack<int> st;
	for (int i = 0; i < n; i++) {
		while (!st.empty() && p[st.top()-1] > p[i]) {
			s.insert(pii(min(i+1,st.top()), max(i+1,st.top())));
			st.pop();
		}
		if (!st.empty())
			s.insert(pii(min(st.top(),i+1), max(st.top(),i+1)));
		st.push(i+1);
	}
	int tmp = -1;
	while (!st.empty()) {
		if (tmp != -1)
			s.insert(pii(min(tmp, st.top()), max(tmp, st.top())));
		tmp = st.top(); st.pop();
	}
		
	stree* root = generate_seg_tree(1, n);
		
	scanf("%d", &q);
	while (q--) {
		scanf("%d%d", &l, &r);
		printf("%d\n", query_seg_tree(root, l, r, l, r, 1, n));
	}
	return 0;
}
