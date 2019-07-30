#include <bits/stdc++.h>

using namespace std;

// when you are too lazy to write mod operation...

template<typename T, long long mod>
class automod {
public:
    automod():num(0){}
    automod(T x):num(x % mod){}
    
    inline automod<T,mod> operator+(automod<T,mod> const& a) {
        return {(0LL+a.num+num) % mod};
    }

    inline automod<T,mod> operator-(automod<T,mod> const& a) {
        return {(((0LL+num-a.num) % mod) + mod) % mod};
    }

    inline automod<T,mod> operator*( automod<T,mod> const& a) {
        return {(1LL*a.num*num) % mod};
    }

    inline automod<T,mod>& operator=( automod<T,mod> const& a) {
        num = a.num % mod;
        return *this;
    }

    inline automod<T,mod>& operator*=( automod<T,mod> const& a) {
        num = (1LL*a.num*num) % mod;
        return *this;
    }

    inline automod<T,mod>& operator+=( automod<T,mod> const& a) {
        num = (0LL+a.num+num) % mod;
        return *this;
    }

    inline automod<T,mod>& operator-=( automod<T,mod> const& a) {
        num = (((0LL+num-a.num) % mod) + mod) % mod;
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
    return 0;
}