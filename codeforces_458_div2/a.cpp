#include <bits/stdc++.h>

using namespace std;

int n,x,h;
unordered_set<int> s;

int main() {
    for (int i = 0; i <= 1000; i++)
        s.insert(i*i);
    scanf("%d", &n);
    h = -1000000;
    while (n--) {
        scanf("%d", &x);
        if (s.find(x) == s.end())
            h = max(h, x);
    }
    printf("%d\n", h);
    return 0;
}