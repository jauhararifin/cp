#include <bits/stdc++.h>
 
using namespace std;
 
int t,b,p,f,h,c;
 
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d%d%d", &b, &p, &f, &h, &c);
        if (h > c) {
            int x = min(p, b / 2);
            printf("%d\n", x * h + min(f, (b-2*x)/2) * c);
        } else {
            int x = min(f, b / 2);
            printf("%d\n", x * c + min(p, (b-2*x)/2) * h);
        }
    }
    return 0;
}
