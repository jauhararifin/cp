#include <bits/stdc++.h>

using namespace std;

long long even_followed_by(int digit) {
    if (digit == 0) return 1LL;
    if (digit == 1) return 5LL;
    long long res = 1;
    for (int i = 0; i < digit - 1; i++)
        res *= 10LL;
    res *= 4LL;
    res += even_followed_by(digit - 1);
    return res;
}

long long odd_followed_by(int digit) {
    if (digit == 0) return 0LL;
    if (digit == 1) return 4LL;
    long long res = 1;
    for (int i = 0; i < digit - 1; i++)
        res *= 10LL;
    res *= 4LL;
    res += odd_followed_by(digit - 1);
    return res;
}

long long even_under(long long num) {
    if (num < 10) {
        long long res = 0;
        for (int i = 0; i <= num; i+= 2)
            res++;
        return res;
    }
    int d = 0;
    stack<long long> st;
    while (num > 0) {
        st.push(num % 10);
        num /= 10;
        d++;
    }

    long long res = 0;
    int before_is_even = 1;
    while (!st.empty()) {
        int cur = st.top(); st.pop();

        if (st.empty()) {
            for (int i = before_is_even ? 0 : 2; i <= cur; i += 2)
                res++;
            break;
        }

        if (cur == 0) {
            d--;
            continue;
        }

        if (before_is_even)
            res += even_followed_by(d-1);
        else
            res += odd_followed_by(d-1);

        for (int i = 1; i < cur; i++)
            if (i % 2)
                res += odd_followed_by(d-1);
            else
                res += even_followed_by(d-1);

        if (cur > 0)
            before_is_even = cur % 2 == 0;
        d--;
    }

    return res;
}

int main() {
    long long a, b;
    scanf("%lld%lld", &a, &b);

    long long t = 1;
    long long eb = even_under(b);
    long long ea = even_under(a-1);

    printf("%lld %lld\n", b - a + 1 - (eb - ea), eb - ea);

    return 0;
}