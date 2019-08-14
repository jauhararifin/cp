#include <bits/stdc++.h>

using namespace std;

template<typename T, long long mod>
class automod {
public:
    automod():num(0) {}
    automod(T x) {
        if (x > mod) num = x % mod;
        else if (x < -mod) num = (x % mod) + mod;
        else num = x;
    }
    automod(const automod<T,mod>& m):num(m.num) {}

    T get() {
        return ((num % mod) + mod) % mod;
    }
    
    automod<T,mod>& operator=(const automod<T,mod>& a) {
        num = a.num;
        return *this;
    }

    automod<T,mod>& operator=(const T& x) {
        num = x;
        if (num > mod) num %= mod;
        else if (num < -mod) num = (num % mod) + mod;
        return *this;
    }

    bool operator==(const automod<T,mod>& a) const {
        return num == a.num;
    }

    bool operator==(const T& a) const {
        return num == a;
    }

    bool operator!=(const automod<T,mod>& a) const {
        return num != a.num;
    }

    bool operator!=(const T& a) const {
        return num != a;
    }

    bool operator<(const automod<T,mod>& a) const {
        return num < a.num;
    }

    bool operator<(const T& a) const {
        return num < a;
    }

    bool operator>(const automod<T,mod>& a) const {
        return num < a.num;
    }

    bool operator>(const T& a) const {
        return num < a;
    }
    
    automod<T,mod> operator+(const automod<T,mod>& a) const {
        long long x = 0LL+num+a.num;
        if (x > mod) x %= mod;
        return {x};
    }

    automod<T,mod>& operator+=(const automod<T,mod>& a) {
        long long temp = 0LL+num+a.num;
        if (temp > mod) temp %= mod;
        num = temp;
        return *this;
    }

    automod<T,mod> operator-(const automod<T,mod>& a) const {
        long long temp = 0LL+num-a.num;
        if (temp < -mod) temp = (temp % mod) + mod;
        return {temp};
    }
    
    automod<T,mod>& operator-=(const automod<T,mod>& a) {
        long long temp = 0LL+num-a.num;
        if (temp < -mod) temp = (temp % mod) + mod;
        num = temp;
        return *this;
    }

    automod<T,mod> operator*(const automod<T,mod>& a) {
        long long temp = 1LL*num*a.num;
        if (temp > mod) temp %= mod;
        return {temp};
    }

    automod<T,mod>& operator*=(const automod<T,mod>& a) {
        long long temp = 1LL*num*a.num;
        if (temp > mod) temp %= mod;
        num = temp;
        return *this;
    }

    template<typename U, long long m>
    friend ostream &operator << (ostream &out, const automod<U,m> &c);

    template<typename U, long long m>
    friend istream &operator >> (istream &in,  automod<U,m> &c);
private:
    T num;
};
template<typename T, long long mod>
ostream& operator<<(ostream &out, const automod<T,mod> &c) {
    out << c.num;
    return out;
}
template<typename T, long long mod>
istream& operator>>(istream &in, automod<T,mod> &c) {
    in >> c.num;
    c.num = ((c.num % mod) + mod) % mod;
    return in;
}
typedef automod<int, 1000000007> intmod;

int t,nl,nr;
char l[100002], r[100002];
intmod ten[100002],tensum[100002];

pair<intmod,intmod> g[100002][10];
pair<intmod,intmod> memo[100002][10][2][2];
pair<intmod,intmod> f(int p, int last, bool b, bool t) {
    if (p < 0) return {0,1};
    if (memo[p][last][b][t].second > -1)
        return memo[p][last][b][t];
    if (last > -1 && !b && !t) {
        // printf("f(%d,%d,%d,%d) = %d %d\n", p, last, b, t, g[p+1][last].first.get(), g[p+1][last].second.get());
        return memo[p][last][b][t] = g[p+1][last];
    }

    int lo = b ? l[p] : 0;
    int hi = t ? r[p] : 9;
    intmod h = 0, c = 0;
    for (int i = lo; i <= hi; i++) {
        intmod x,y;
        tie(x,y) = f(p-1, i, b && i == lo, t && i == hi);
        c += y;
        if (i != last) h += ten[p] * i * y + x;
        else h += x;
    }
    // printf("f(%d,%d,%d,%d) = %d %d --> lo=%d, hi=%d\n", p, last, b, t, h.get(), c.get(), lo, hi);
    return memo[p][last][b][t] = {h,c};
}

int main() {
    ten[0] = 1; for (int i = 1; i <= 100001; i++) ten[i] = ten[i-1] * 10;
    tensum[0] = 1; for (int i = 1; i <= 100001; i++) tensum[i] = tensum[i-1] + ten[i];
    for (int last = 0; last < 10; last++)
        for (int n = 1; n <= 100000; n++) {
            g[n][last] = {ten[n-1] * ten[n-1] * (45 - last), ten[n]};
            if (n > 1)
                g[n][last].first += ten[n-2] * tensum[n-2] * 9 * 45;
        }

    scanf("%d", &t);
    while (t--) {
        memset(memo, -1, sizeof memo);
        memset(l, 0, sizeof l);
        memset(r, 0, sizeof r);
        scanf("%d", &nl); scanf("%s", l);
        scanf("%d", &nr); scanf("%s", r);
        reverse(l, l + nl);
        reverse(r, r + nr);
        for (int i = 0; i < nl; i++) l[i] -= '0';
        for (int i = 0; i < nr; i++) r[i] -= '0';
        printf("%d\n", f(nr-1,-1,1,1).first.get());
    }
    return 0;
}