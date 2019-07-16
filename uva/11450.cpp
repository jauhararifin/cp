#include <bits/stdc++.h>

using namespace std;

int t,m,c,k,x;

int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &m, &c);
        set<int> pos; pos.insert(0);
        for (int i = 0; i < c; i++) {
            set<int> next;
            scanf("%d", &k);
            while (k--) {
                scanf("%d", &x);
                for (int w : pos)
                    if ((w + x) <= m)
                        next.insert(w+x);
            }
            pos = next;
        }
        if (pos.size() == 0) printf("no solution\n");
        else {
            int m = -1; for (int x : pos) m = max(m, x);
            printf("%d\n", m);
        }
    }
    return 0;
}