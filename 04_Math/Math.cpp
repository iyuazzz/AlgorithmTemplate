#include <bits/stdc++.h>

namespace Math {
    constexpr int Mod = 998244353;

    int power(int x, int n) {
        int ret = 1;
        while(n > 0) {
            if(n & 1) ret = 1ll * ret * x % Mod;
            n >>= 1;
            x = 1ll * x * x % Mod;
        }
        return ret;
    }

    template<class T>
    T lcm(T a, T b) {return a / std::__gcd(a, b) * b;}

    bool isPrim(int x) {
        if(x == 0 || x == 1) return false;
        if(x == 2 || x == 3) return true;
        for (int i = 2; 1ll * i * i <= x; ++ i) {
            if(x % i == 0) {
                return false;
            }
        }
        return true;
    }

    template<class T>
    std::vector<T> getPrimFac(T x) {
        std::vector<T> table;
        for (int i = 2; 1ll * i * i <= x; ++ i) {
            if(x % i != 0) continue;
            table.emplace_back(i);
            while(x % i == 0) x /= i;
        }
        if(x != 1) table.emplace_back(x);
        return table;
    }

    std::pair<std::vector<int>, std::vector<int> > getPrimNum(int N) {
        std::vector<int> is(N + 1, 1), cur;
        is[0] = is[1] = 0;
        for (int i = 2; i <= N; ++ i) {
            if(is[i]) cur.emplace_back(i);
            for (int j = 0; j < cur.size() && 1ll * i * cur[j] <= N; ++ j) {
                is[i * cur[j]] = 0;
                if(i % cur[j] == 0) break;
            }
        }
        return std::make_pair(is, cur);
    }
};