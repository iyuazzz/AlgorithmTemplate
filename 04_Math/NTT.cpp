#include <bits/stdc++.h>
//  should first  Poly::init_w(L);
//  (1 << L) should bigger than poly'len   (n + m - 1)
using poly = std::vector<int>;
constexpr int Mod = 998244353;
namespace modular {
	inline int add(int a, int b) {return a + b >= Mod ? a + b - Mod : a + b;}
	inline int dec(int a, int b) {return a - b < 0 ? a - b + Mod : a - b;}
	inline int mul(int a, int b) {return 1ll * a * b % Mod;}
	inline int power(int x, int n) {
		int ret = 1;
		for (; n > 0; n >>= 1, x = mul(x, x)) {
			if(n & 1) ret = mul(ret, x);
		}
		return ret;
	}
	inline int inv(int x) {return power(x, Mod - 2);}
} using namespace modular;

namespace Poly {
	int Len, bit, invv[24];
	std::vector<int> rev[24], w[24];
    /*
        1 << 17   -->   131072
        1 << 18   -->   262144
        1 << 19   -->   524288
        1 << 20   -->   1048576
        1 << 21   -->   2097152
        1 << 22   -->   4194304
    */
    //  poly^n  ->  x ^ [0, n - 1]
	inline void init_w(int L = 18) { // (1 << L) should bigger than poly'len
		std::fill(invv, invv + 24, 0);  
		int lm = (1 << L);
		w[L - 1].resize(1 << (L - 1), 0); w[L - 1][0] = 1;
		w[L - 1][1] = power(3, (Mod - 1) / lm);
		for (int i = 2; i < lm / 2; ++ i) w[L - 1][i] = mul(w[L - 1][i - 1], w[L - 1][1]);
		for (int i = L - 2; i >= 0; -- i) {
			w[i].resize(1 << i, 0);
			for (int j = 0; j < (1 << i); ++ j) {
				w[i][j] = w[i + 1][j << 1];
			}
		}
	}
	inline void init_rev(int lm) {
		Len = 1; bit = 0;
		while(Len < lm) Len <<= 1, ++ bit;
		if(invv[bit]) return ;
		invv[bit] = inv(1 << bit);
		rev[bit].resize(Len, 0);
		rev[bit][0] = 0;
		for (int i = 1; i < Len; ++ i) {
			rev[bit][i] = ((rev[bit][i >> 1] >> 1) | ((i & 1) << (bit - 1)));
		}
	}
	inline void NTT(poly& A, int type) {
		for (int i = 0; i < Len; ++ i) if(i < rev[bit][i]) {
			std::swap(A[i], A[rev[bit][i]]);
		}	
		for (int i = 1, t = 0; i < Len; i <<= 1, ++ t) {
			for (int j = 0; j < Len; j += (i << 1)) {
				for (int k = 0; k < i; ++ k) {
					int x = A[j + k], y = mul(w[t][k], A[j + k + i]);
					A[j + k] = add(x, y);
					A[j + k + i] = dec(x, y);
				}
			}
		}
		if(type == 1) return ;
		reverse(++ A.begin(), A.end());
		for (int i = 0; i < Len; ++ i) A[i] = mul(A[i], invv[bit]);
	}
	poly operator * (poly a, poly b) {
		int n = a.size(), m = b.size(), t = n + m - 1;
		if(n <= 30 || m <= 30) {
			poly c(t, 0);
			for (int i = 0; i < n; ++ i) if(a[i]) {
				for (int j = 0; j < m; ++ j) {
					c[i + j] = add(c[i + j], mul(a[i], b[j]));
				}
			}
			return c;
		}
		init_rev(t);
		a.resize(Len); NTT(a, 1);
		b.resize(Len); NTT(b, 1);
		for (int i = 0; i < Len; ++ i) {
			a[i] = mul(a[i], b[i]);
		}
		NTT(a, -1); a.resize(t);
		return a;
	}
	poly poly_mul(poly a, poly b) {return a * b;}
}
