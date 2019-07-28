#include <bits/stdc++.h>

using namespace std;

long long n;

int guess(long long a, long long b) {
    cout<<a<<" "<<b<<endl;
    fflush(stdout);
    int res; scanf("%d", &res);
    if (res == 0) exit(0);
    return res;
}

int main() {
    srand(time(0));
    ios::sync_with_stdio(0);
    cin>>n;

    long long x1 = 1; long long y1 = 1;
    long long x2 = n; long long y2 = n;
    long long x3 = n; long long y3 = n;
    
    while (1) {
        if (rand() % 3 == 0) {
            int r = guess((x1+x2)/2, (y1+y2)/2);
            if (r == 1) x1 = min((x1+x2)/2 + 1, x2);
            else if (r == 2) y1 = min((y1+y2)/2 + 1, y2);
            else { x2 = max(x1, (x1+x2)/2 - 1); y2 = max(y1, (y1+y2)/2 - 1); }
        } else if (rand() % 2 == 0) {
            int r = guess((x1+x2)/2, y2);
            if (r == 1) x1 = min(x2, (x1+x2)/2 + 1);
            else if (r == 2) {
                y1 = min(y3, y2 + 1);
                x3 = x2;
                y2 = y3;
            } else x2 = max(x1, (x1+x2)/2 - 1);
        } else {
            int r = guess(x2, (y1+y2)/2);
            if (r == 1) {
                x1 = min(x3, x2 + 1);
                x2 = x3;
                y3 = y2;
            } else if (r == 2) y1 = min(y2, (y1+y2)/2 + 1);
            else y2 = max(y1, (y1+y2)/2 - 1);
        }
    }

    return 0;
}