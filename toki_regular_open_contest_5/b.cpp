#include <bits/stdc++.h>

using namespace std;

int a,b,m;
set<int> s;
set<pair<int,int> > p;

int main() {
    scanf("%d%d%d", &a, &b, &m);
    s.insert(a);
    s.insert(b);
    while (p.find(make_pair(a,b)) == p.end()) {
        int c = (a + b) % m;
        p.insert(make_pair(a,b));
        s.insert(c);
        a = b;
        b = c;
    }
    printf("%d\n", s.size());
    return 0;
}