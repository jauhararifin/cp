#include <bits/stdc++.h>

using namespace std;

template<typename T>
class square_matrix {
public:
    square_matrix() {
        n = 1;
        arr = new T[1];
    }

    square_matrix(int size):n(size) {
        arr = new T[n*n];
    }
    
    square_matrix(const square_matrix<T>& m) {
        n = m.n;
        arr = new T[n*n];
        for (int i = 0; i < n*n; i++)
            arr[i] = m.arr[i];
    }

    square_matrix(square_matrix<T>&& m) {
        n = m.n;
        arr = m.arr;
        m.arr = 0;
        m.n = 0;
    }

    ~square_matrix() {
        if (arr) delete [] arr;
    }

    square_matrix<T>& resize(int size) {
        delete [] arr;
        n = size;
        arr = new T[n*n];
    }

    square_matrix<T>& operator=(square_matrix<T> a) {
        swap(arr, a.arr);
        swap(n, a.n);
        return *this;
    }

    T* operator[](int i) { return arr + i * n; }

    bool operator==(const square_matrix<T>& a) const {
        if (this == &a) return 1;
        if (n != a.n) return 0;
        for (int i = 0; i < n*n; i++)
            if (arr[i] != a.arr[i]) return 0;
        return 1;
    }

    square_matrix<T> operator+(const square_matrix<T>& a) const {
        assert(n == a.n);
        square_matrix<T> res(n);
        for (int i = 0; i < n*n; i++)
            res.arr[i] = arr[i] + a.arr[i];
        return res;
    }

    square_matrix<T>& operator+=(const square_matrix<T>& a) {
        assert(n == a.n);
        for (int i = 0; i < n*n; i++)
            arr[i] += a.arr[i];
        return (*this);
    }

    square_matrix<T> operator-(const square_matrix<T>& a) const {
        square_matrix<T> res(n);
        for (int i = 0; i < n*n; i++)
            res.arr[i] = arr[i] - a.arr[i];
        return res;
    }

    square_matrix<T>& operator-=(const square_matrix<T>& a) {
        assert(n == a.n);
        for (int i = 0; i < n*n; i++)
            arr[i] -= a.arr[i];
        return (*this);
    }

    square_matrix<T> operator*(const square_matrix<T>& a) const {
        if (n <= 512) return naive_mul(a);
        
        int s = n;
        while (__builtin_popcount(s) != 1) s += s & -s;
        double strassen_ratio = pow(7.0, log2((double) s/ (double) n));
        double naive_ratio = pow(11.0, log2((double) n / 512.0));
        if (strassen_ratio < naive_ratio) return strassen_mul(a);
        return naive_mul(a);
    }

    square_matrix<T> operator*(const T& scalar) const {
        square_matrix<T> res(n);
        for (int i = 0; i < n*n; i++) res.arr[i] = arr[i] * scalar;
        return res;
    }

    vector<T> operator*(const vector<T>& v) const {
        assert(n == (int) v.size());
        vector<T> res(n);
        for (int i = 0; i < n; i++) {
            res[i] = arr[i*n] * v[0];
            for (int j = 1; j < n; j++)
                res[i] += arr[i*n+j] * v[j];
        }
        return res;
    }

    square_matrix<T>& operator*=(const square_matrix<T>& a) {
        assert(n == a.n);
        square_matrix<T> result = (*this) * a;
        (*this) = result;
        return *this;
    }

    square_matrix<T>& operator*=(const T& scalar) {
        for (int i = 0; i < n*n; i++) arr[i] *= scalar;
    }

    square_matrix<T> operator/(const T& scalar) const {
        square_matrix<T> res(n);
        for (int i = 0; i < n*n; i++) res.arr[i] = arr[i] / scalar;
        return res;
    }

    square_matrix<T>& operator/=(const T& scalar) {
        for (int i = 0; i < n*n; i++) arr[i] /= scalar;
    }

    template<typename U>
    friend ostream& operator<<(ostream& os, const square_matrix<U>& m);

    template<typename U>
    friend istream& operator>>(istream& is, square_matrix<U>& m);

private:

    square_matrix<T> naive_mul(const square_matrix<T>& m) const {
        assert(n == m.n);
        square_matrix<T> res(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                res[i][j] = 0;
                for (int k = 0; k < n; k++)
                    res[i][j] += this->arr[i*n+k] * m.arr[k*n+j];
            }
        return res;
    }

    square_matrix<T> strassen_mul(const square_matrix<T>& m) const {
        assert(n == m.n);
        if (n <= 512) return naive_mul(m);
        
        int s = n;
        while (__builtin_popcount(s) != 1)
            s += s & -s;

        square_matrix<T> a11(s/2), a12(s/2), a21(s/2), a22(s/2);
        square_matrix<T> b11(s/2), b12(s/2), b21(s/2), b22(s/2);
        for (int i = 0; i < s; i++)
            for (int j = 0; j < s; j++) {
                T va = i >= n || j >= n ? 0 : arr[i*n+j];
                T vb = i >= n || j >= n ? 0 : m.arr[i*n+j];
                if (i < s/2 && j < s/2) { a11[i][j] = va; b11[i][j] = vb; }
                else if (i < s/2) { a12[i][j-s/2] = va; b12[i][j-s/2] = vb; }
                else if (j < s/2) { a21[i-s/2][j] = va; b21[i-s/2][j] = vb; }
                else { a22[i-s/2][j-s/2] = va; b22[i-s/2][j-s/2] = vb; }
            }
        
        auto m1 = (a11 + a22).strassen_mul(b11 + b22);
        auto m2 = (a21 + a22).strassen_mul(b11);
        auto m3 = a11.strassen_mul(b12 - b22);
        auto m4 = a22.strassen_mul(b21 - b11);
        auto m5 = (a11 + a12).strassen_mul(b22);
        auto m6 = (a21 - a11).strassen_mul(b11 + b12);
        auto m7 = (a12 - a22).strassen_mul(b21 + b22);

        auto c11 = m1 + m4 - m5 + m7;
        auto c12 = m3 + m5;
        auto c21 = m2 + m4;
        auto c22 = m1 - m2 + m3 + m6;

        square_matrix<T> c(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i < s/2 && j < s/2) c[i][j] = c11[i][j];
                else if (i < s/2) c[i][j] = c12[i][j-s/2];
                else if (j < s/2) c[i][j] = c21[i-s/2][j];
                else c[i][j] = c22[i-s/2][j-s/2];
        
        return c;
    }

    T* arr;
    int n;
};

template<typename U>
square_matrix<U> operator*(const U& scalar, const square_matrix<U>& m) {
    return m * scalar;
}

template<typename U>
ostream& operator<<(ostream& os, const square_matrix<U>& m) {
    for (int i = 0; i < m.n; i++) {
        os<<m.arr[i*m.n];
        for (int j = 1; j < m.n; j++)
            os<<" "<<m.arr[i*m.n+j];
        os<<endl;
    }
    return os;
}

template<typename U>
istream& operator>>(const istream& is, square_matrix<U>& m) {
    for (int i = 0; i < m.n * m.n; i++) is>>m.arr[i];
    return is;
}

template<typename T>
square_matrix<T> identity(int n) {
    square_matrix<T> res(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            res[i][j] = i == j ? 1 : 0;
    return res;
}

template<typename T>
square_matrix<T> zeros(int n) {
    square_matrix<T> res(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            res[i][j] = 0;
    return res;
}

int main() {
    square_matrix<int> m(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    square_matrix<int> p(2);
    p[0][0] = 2; p[0][1] = 1;
    p[1][0] = 0; p[1][1] = 1;

    cout<<"m ="<<endl<<m<<endl;
    cout<<"p ="<<endl<<p<<endl;
    cout<<"m + p"<<endl<<(m + p)<<endl;
    cout<<"m - p"<<endl<<(m - p)<<endl;
    cout<<"m * p"<<endl<<(m * p)<<endl;

    cout<<"m ="<<endl<<m<<endl;
    cout<<"m*2"<<endl<<m*2<<endl;
    cout<<"2*m"<<endl<<2*m<<endl;


    for (int n = 2; n <= 32; n+=n) {
        square_matrix<int> x(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                x[i][j] = rand() % 5;
        
        square_matrix<int> id = identity<int>(n);
        clock_t t; 
        t = clock(); 
        for (int i = 0; i < 100000; i++)
            id *= x;
        t = clock() - t;
        double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
        cout<<"multiply "<<n<<"x"<<n<<" matrix 30000 times: "<<time_taken<<" seconds"<<endl;
    }
    
    return 0;
}