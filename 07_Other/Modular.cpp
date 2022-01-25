#include <bits/stdc++.h>

using ll = long long;
constexpr int MOD = 1e9 + 7;

namespace modular {
	inline int add(int a, int b) {return a + b >= MOD ? a + b - MOD : a + b;}
	inline int dec(int a, int b) {return a - b < 0 ? a - b + MOD : a - b;}
	inline int mul(int a, int b) {return 1ll * a * b % MOD;}
	inline int power(int x, int n) {
		int ret = 1;
		for (; n > 0; n >>= 1, x = mul(x, x)) {
			if(n & 1) ret = mul(ret, x);
		}
		return ret;
	}
	inline int inv(int x) {return power(x, MOD - 2);}
} using namespace modular;

struct modint {
 
private:
 
    int v;
 
    static int minv(int a, int m) {
        a %= m;
        assert(a);
        return a == 1 ? 1 : int(m - ll(minv(m, a)) * ll(m) / a);
    }
 
public:
 
    modint() : v(0) {}
    modint(ll v_) : v(int(v_ % MOD)) { if (v < 0) v += MOD; }
    explicit operator int() const { return v; }
    friend std::ostream& operator << (std::ostream& out, const modint& n) { return out << int(n); }
    friend std::istream& operator >> (std::istream& in, modint& n) { ll v_; in >> v_; n = modint(v_); return in; }
 
    friend bool operator == (const modint& a, const modint& b) { return a.v == b.v; }
    friend bool operator != (const modint& a, const modint& b) { return a.v != b.v; }
	int val() const {
		return v;
	}
    modint inv() const {
        modint res;
        res.v = minv(v, MOD);
        return res;
    }
    friend modint inv(const modint& m) { return m.inv(); }
    modint neg() const {
        modint res;
        res.v = v ? MOD-v : 0;
        return res;
    }
    friend modint neg(const modint& m) { return m.neg(); }
 
    modint operator- () const {
        return neg();
    }
    modint operator+ () const {
        return modint(*this);
    }
 
    modint& operator ++ () {
        v ++;
        if (v == MOD) v = 0;
        return *this;
    }
    modint& operator -- () {
        if (v == 0) v = MOD;
        v --;
        return *this;
    }
    modint& operator += (const modint& o) {
        v += o.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    modint& operator -= (const modint& o) {
        v -= o.v;
        if (v < 0) v += MOD;
        return *this;
    }
    modint& operator *= (const modint& o) {
        v = int(ll(v) * ll(o.v) % MOD);
        return *this;
    }
    modint& operator /= (const modint& o) {
        return *this *= o.inv();
    }
 
    friend modint operator ++ (modint& a, int) { modint r = a; ++a; return r; }
    friend modint operator -- (modint& a, int) { modint r = a; --a; return r; }
    friend modint operator + (const modint& a, const modint& b) { return modint(a) += b; }
    friend modint operator - (const modint& a, const modint& b) { return modint(a) -= b; }
    friend modint operator * (const modint& a, const modint& b) { return modint(a) *= b; }
    friend modint operator / (const modint& a, const modint& b) { return modint(a) /= b; }
};