#include <bits/stdc++.h>

using namespace std;

int h1,a1,c1,h2,a2;
vector<char> action;

int main() {
    scanf("%d%d%d%d%d", &h1, &a1, &c1, &h2, &a2);
    while (h2 > 0) {
        if (a1 >= h2 || h1 - a2 > 0) {
            action.push_back(1);
            h2 -= a1;
        } else {
            action.push_back(0);
            h1 += c1;
        }
        h1 -= a2;
    }
    printf("%d\n", (int) action.size());
    for (int i = 0; i < (int) action.size(); i++)
        printf("%s\n", action[i] ? "STRIKE" : "HEAL");
    return 0;
}