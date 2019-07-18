#include <bits/stdc++.h>

using namespace std;

int n,m,a,b,g0,x,y,z,p[3000][3000],r[3000][3000];

int main() {
    scanf("%d%d%d%d", &n, &m, &a, &b);
    scanf("%d%d%d%d", &g0, &x, &y, &z);

    long long q = g0;
    for (int i = 0; i < n*m; i++) {
        p[i/m][i%m] = q;
        q = (q * x + y) % (long long) z;
    }

    for (int j = 0; j < m; j++) {
        deque<int> dq;
        for (int i = 0; i < n; i++) {
            while (!dq.empty() && dq.back() > p[i][j])
                dq.pop_back();
            dq.push_back(p[i][j]);
            if (i >= a && !dq.empty() && dq.front() == p[max(0,i-a)][j])
                dq.pop_front();
            r[i][j] = dq.front();
        }
    }

    long long h = 0;
    for (int i = a-1; i < n; i++) {
        deque<int> dq;
        for (int j = 0; j < m; j++) {
            while (!dq.empty() && dq.back() > r[i][j])
                dq.pop_back();
            dq.push_back(r[i][j]);
            if (j >= b && !dq.empty() && dq.front() == r[i][max(0,j-b)])
                dq.pop_front();
            if (j >= b - 1)
                h += (long long) dq.front();
        }
    }

    printf("%I64d\n", h);
    return 0;
}