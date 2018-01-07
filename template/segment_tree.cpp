#include <bits/stdc++.h>

using namespace std;

class segment_tree {
public:
    segment_tree(int n, int* v) {
        arr = new int[4*n+1];
        init_segment_tree(1, 0, n-1, v);
    }

    int query(int left, int right) {
        return recursive_query(1, 0, n-1, left, right-1);
    }

    int n;
    int *arr; 
private:
    int& init_segment_tree(int node, int left, int right, int* v) {
        if (left == right) return arr[node] = v[left];
        int& l = init_segment_tree(node*2, left, (left+right)/2, v);
        int& r = init_segment_tree(node*2+1, (left+right)/2+1, right, v);
        return arr[node] = max(l,r);
    }
    int recursive_query(int node, int l, int r, int left, int right) {
        if (r < left || l > right) return -1;
        if (l >= left && r  <= right) return arr[node];
        int tl = recursive_query(node*2, l, (l+r)/2, left, right);
        int tr = recursive_query(node*2+1, (l+r)/2+1, r, left, right);
        return max(tl, tr);
    }
};

int main() {
    return 0;
}