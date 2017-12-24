#include <bits/stdc++.h>

using namespace std;

int k,n;
char s[5000][5001];

int diff[5000];
bool possible(char *s, int *to) {
    int c = 0; 
    unordered_set<char> st;
    for (int i = 0; i < n; i++) {
        if (s[i] != to[i])
            diff[c++] = i;
        st.insert(s[i]);
    }
    if (c == 0 && st.size() < n)
        return 1;
    if (c == 2 && to[diff[0]] == s[diff[1]] && to[diff[1]] == s[diff[0]]) // and if swapped is true
        return 1;
    return 0;
}

int main() {
    scanf("%d%d", &k, &n);
    for (int i = 0; i < k; i++)
        scanf("%s", s[i]);
    vector<int> d;
    for (int i = 0; i < n; i++)
        if (s[0][i] != s[1][i])
            d.push_back(i);
    if (d.size() )
    return 0;
}