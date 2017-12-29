#include <bits/stdc++.h>

using namespace std;

int n,k,a[200000],b;
bool v[200001];

int main() {
    scanf("%d%d", &n, &k);
    memset(v, 0, sizeof v);
    for (int i = 0; i < k; i++)
        scanf("%d", a + i), v[a[i]] = 1;

    b = 1;
    stack<int> s;
    for (int i = 0; i < k; i++) {
        s.push(a[i]);
        while (!s.empty() && s.top() == b) {
            s.pop();
            b++;
        }
    }
    set<int> remaining;
    for (int i = 1; i <= n; i++)
        if (!v[i])
            remaining.insert(i);
    while (!remaining.empty()) {
        if (s.empty()) {
            int t = *(--remaining.end());
            remaining.erase(t);
            s.push(t);
            a[k++] = t;
        } else {
            int t = s.top();
            if (remaining.find(t-1) != remaining.end())
                s.push(t-1), remaining.erase(t-1), a[k++] = t - 1;
            else
                break;
        }
        while (!s.empty() && s.top() == b) {
            s.pop();
            b++;
        }
    }

    if (b != n + 1)
        printf("-1\n");
    else {
        for (int i = 0; i < n - 1; i++)
            printf("%d ", a[i]);
        printf("%d\n", a[n-1]);
    }

    return 0;
}