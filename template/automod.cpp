#include <bits/stdc++.h>

using namespace std;

// when you are too lazy to write mod operation...

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

int main() {
    automod<int, 29> n(31);
    n *= 27;
    n += 10;
    n -= 7;
    cout<<n<<endl;

    n = 32;
    cout<<n<<endl;

    n = -1;
    cout<<n<<endl;
    
    return 0;
}