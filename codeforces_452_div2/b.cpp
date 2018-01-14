#include <bits/stdc++.h>

using namespace std;

int n, a[24];

bool is_possible(pair<int,int> mon, int m) {
    mon.first %= 12;
    if (m == 31)
        return mon.first == 0 || mon.first == 2 || mon.first == 4 || mon.first == 6 || mon.first == 7 || mon.first == 9 || mon.first == 11;
    else if (m == 30)
        return mon.first == 3 || mon.first == 5 || mon.first == 8 || mon.first == 10;
    else if (mon.first == 1)
        return (m == 28 && mon.second != 0) || (m == 29 && mon.second == 0);
    return 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", a + i);
    
    set<pair<int,int> > possible;
    for (int i = 0; i < 12; i++) {
        possible.insert(make_pair(i,0));
        possible.insert(make_pair(i,1));
        possible.insert(make_pair(i,2));
        possible.insert(make_pair(i,3));
    }
    for (int i = 0; i < n; i++) {
        int x = a[i];
        vector<pair<int,int> > v;
        for (pair<int,int> p : possible) {
            pair<int,int> temp = make_pair(p.first + i, p.second + (p.first + i)/12);
            temp.second %= 4;
            if (!is_possible(temp, x))
                v.push_back(p);
        }
        for (pair<int,int> p : v) possible.erase(p);
        // for (pair<int,int> p : possible) printf("Possible %d %d\n", p.first, p.second);
        // printf("===================\n");
    }
    if (possible.size() > 0)
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}