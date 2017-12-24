#include <bits/stdc++.h>

using namespace std;

int n,m,k;
bool pos[1000001];

int main() {
    scanf("%d%d%d", &n, &m, &k);
    memset(pos, 0, sizeof pos);
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        pos[x] = 1;
    }
    
    int answer = 0;
    deque<int> dque;
    for (int i = 1; i <= 1000000; i++) {
        if (pos[i])
            dque.push_back(i);
        while (!dque.empty() && i - dque.front() >= m)
            dque.pop_front();
        while (dque.size() >= k) {
            answer++;
            dque.pop_back();   
        }
    }

    printf("%d\n", answer);
    return 0;
}