#include <bits/stdc++.h>

using namespace std;

template<typename T>
class polynomial {
public:
	vector<T> arr;
	bool modEnable = false;
	T mod;

	void useMod(T m) {
		mod = m;
		modEnable = true;
	}

	T& operator[](const uint i) {
		if (i >= arr.size())
			arr.resize(i + 1, T());
		return arr[i];
	};
	uint degree() {
		return arr.size() - 1;
	};

	template<typename S>
	friend ostream& operator<<(ostream& os, polynomial<S> a);

	template<typename S>
	friend polynomial<S> operator+(const polynomial<S>& a, const polynomial<S>& b);

	template<typename S>
	friend polynomial<S> operator*(const polynomial<S>& a, const polynomial<S>& b);

	template<typename S>
	friend polynomial<S> operator-(polynomial<S> a);

	template<typename S>
	friend polynomial<S> operator-(polynomial<S> a, polynomial<S> b);
};

template<typename T>
ostream& operator<<(ostream& os, polynomial<T> a) {
	os<<a.arr[0];
	for (int i = 1; i < (int) a.arr.size(); i++)
		os<<" "<<a.arr[i];
	return os;
};

template<typename S>
polynomial<S> operator+(const polynomial<S>& a, const polynomial<S>& b) {
	polynomial<S> res;
	for (int i = 0; i < a.arr.size() || i < b.arr.size(); i++)
		if (!a.modEnable)
			res[i] = (i < a.arr.size() ? a.arr[i] : S()) + (i < b.arr.size() ? b.arr[i] : S());
		else
			res[i] = (((i < a.arr.size() ? a.arr[i] : S()) % a.mod) + ((i < b.arr.size() ? b.arr[i] : S()) % a.mod)) % a.mod;
	return res;
};

template<typename S>
polynomial<S> operator*(const polynomial<S>& a, const polynomial<S>& b) {
	polynomial<S> res;
	for (int i = 0; i < a.arr.size(); i++)
		for (int j = 0; j < b.arr.size(); j++)
			if (!a.modEnable)
				res[i+j] = res[i+j] + (i < a.arr.size() ? a.arr[i] : S()) * (j < b.arr.size() ? b.arr[j] : S());
			else
				res[i+j] = (res[i+j] + (((i < a.arr.size() ? a.arr[i] : S()) % a.mod) * ((j < b.arr.size() ? b.arr[j] : S()) % a.mod)) % a.mod) % a.mod;
	return res;
};

template<typename S>
polynomial<S> operator-(polynomial<S> a) {
	for (int i = 0; i < (int) a.arr.size(); i++) {
		a.arr[i] *= -1;
		if (a.modEnable)
			a.arr[i] = ((a.arr[i] % a.mod) + a.mod) % a.mod;
	}
	return a;
};

template<typename S>
polynomial<S> operator-(polynomial<S> a, polynomial<S> b) {
	return a + (-b);
};

template<typename S>
polynomial<S> karatsuba_multiply(polynomial<S> a, polynomial<S> b) {
	if (a.degree() <= 1 || b.degree() <= 1)
		return a*b;
	polynomial<S> x0,x1,y0,y1;
	int m = max(a.degree(), b.degree())/2;
	for (int i = 0; i <= a.degree(); i++)
		if (i < m)
			x0[i] = a[i];
		else
			x1[i-m] = a[i];
	for (int i = 0; i <= b.degree(); i++)
		if (i < m)
			y0[i] = b[i];
		else
			y1[i-m] = b[i];
	polynomial<S> z2 = karatsuba_multiply(x1,y1);
	polynomial<S> z0 = karatsuba_multiply(x0,y0);
	polynomial<S> z1 = karatsuba_multiply(x1 + x0,y1 + y0) - z2 - z0;

	for (int i = 0; i <= z1.degree(); i++)
		z0[i+m] += z1[i];
	for (int i = 0; i <= z2.degree(); i++)
		z0[i+2*m] += z2[i];

	return z0;
}

int main() {
	ios::sync_with_stdio(0);
	int t,n;
	cin>>t;
	while (t--) {
		cin>>n;
		polynomial<int> a,b;
		for (int i = 0; i < n+1; i++)
			cin>>a[n-i];
		for (int i = 0; i < n+1; i++)
			cin>>b[n-i];
		polynomial<int> c = karatsuba_multiply(a,b);

		for (int i = c.degree(); i > 0; i--)
			cout<<c[i]<<" ";
		cout<<c[0]<<endl;
	}
	return 0;
}