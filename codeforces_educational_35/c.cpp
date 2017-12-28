#include <bits/stdc++.h>

using namespace std;

long long a,b,c;

int main() {
    scanf("%lld%lld%lld", &a, &b, &c);
    
    long long lcm = (a * b) / __gcd(a, b);
    lcm = (lcm * c) / __gcd(lcm, c);

    for (long long i = 0; i < a; i++)
        for (long long j = 0; j < a; j++) {
            long long pa = lcm / a;
            long long pb = (lcm - i) / b;
            long long pc = (lcm - j) / c;
            long long pab = __gcd(a, b) == 1 ? lcm / (a * b) : 0;
            long long pac = __gcd(a, c) == 1 ? lcm / (a * c) : 0;
            long long pbc = __gcd(b, c) == 1 ? lcm / (b * c) : 0;
            long long pabc = __gcd(c, __gcd(a,b)) == 1 ? lcm / (a*b*c) : 0;
            
            long long cover = pa + pb + pc - (pab + pac + pbc) + pabc;
            if (cover == lcm) {
                printf("YES\n");
                return 0;
            }
        }
    printf("NO\n");

    return 0;
}