#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> adj[1000];
bool leaf[1000];

int main() {
    scanf("%d", &n);
    memset(leaf, -1, sizeof leaf);
    for (int i = 1; i < n; i++) {
        int x; scanf("%d", &x); x--;
        adj[x].push_back(i);
        leaf[x] = 0;
    }

    for (int i = 0; i < n; i++)
        if (!leaf[i]) {
            int c = 0;
            for (int x : adj[i])
                if (leaf[x]) c++;
            if (c < 3) {
                printf("No\n");
                return 0;
            }
        }
    printf("Yes\n");
}