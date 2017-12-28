#include <bits/stdc++.h>

using namespace std;

string s;
pair<int,int> conn[1000000];
set<int> candidate;
bool exists[1000000];

int main() {
    getline(cin, s);
    int n = (int) s.length();
    if (n == 1) {
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        conn[i] = make_pair(i - 1, i == n - 1 ? -1 : i + 1);
        candidate.insert(i);
        exists[i] = 1;
    }

    int sz = n;
    int h = 0;
    while (!candidate.empty() && sz > 1) {

        set<int> temp;
        vector<int> erased;
        for (int i : candidate) {
            bool diff = (conn[i].first > -1 && s[i] != s[conn[i].first]) ||
                (conn[i].second > -1 && s[i] != s[conn[i].second]);
            if (diff) erased.push_back(i), exists[i] = 0;
        }
        for (int i : erased) {
            if (conn[i].first > -1 && exists[conn[i].first])
                temp.insert(conn[i].first);
            if (conn[i].second > -1 && exists[conn[i].second])
                temp.insert(conn[i].second);
            sz--;
            if (conn[i].first > -1) conn[conn[i].first].second = conn[i].second;
            if (conn[i].second > -1) conn[conn[i].second].first = conn[i].first;
        }

        if (erased.size() <= 0)
            break;
        h++;
        candidate = temp;
    }

    printf("%d\n", h);
    return 0;
}