#include <bits/stdc++.h>

using namespace std;

int n,x;
map<int,int> mp;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &x), mp[x]++;
    bool win = 0;
    for (auto i = mp.begin(); !win && i != mp.end(); i++)
        if (i->second % 2)
            win = 1;
    printf("%s\n", win ? "Conan" : "Agasa");

    return 0;
}