// https://www.luogu.com.cn/problem/solution/P1742

#include<bits/stdc++.h>

typedef long long ll;
using namespace std;

typedef long double ld;

struct vec {
    double x, y;

    vec(const double &x0 = 0, const double &y0 = 0) : x(x0), y(y0) {}

    vec operator+(const vec &t) const { return vec(x + t.x, y + t.y); }

    vec operator-(const vec &t) const { return vec(x - t.x, y - t.y); }

    vec operator*(const double &t) const { return vec(x * t, y * t); }

    vec operator/(const double &t) const { return vec(x / t, y / t); }

    const double len2() const { return x * x + y * y; }

    const double len() const { return sqrt(len2()); }

    vec norm() const { return *this / len(); }

    vec rotate_90_c() { return vec(y, -x); }
};

double dot(const vec &a, const vec &b) { return a.x * b.x + a.y * b.y; }

double crs(const vec &a, const vec &b) { return a.x * b.y - a.y * b.x; }

vec lin_lin_int(const vec &p0, const vec &v0, const vec &p1, const vec &v1) {
    double t = crs(p1 - p0, v1) / crs(v0, v1);
    return p0 + v0 * t;
}

vec circle(const vec &a, const vec &b, const vec &c) {
    return lin_lin_int((a + b) / 2, (b - a).rotate_90_c(), (a + c) / 2, (c - a).rotate_90_c());
}

mt19937_64 mrand(chrono::steady_clock::now().time_since_epoch().count());
// 返回的是直径
double solve(int n, vector<vec> pot) {
    shuffle(pot.begin(), pot.end(), mrand);
    vec o;
    double r2 = 0;
    for (int i = 0; i < n; i++) {
        if ((pot[i] - o).len2() > r2) {
            o = pot[i], r2 = 0;
            for (int j = 0; j < i; j++) {
                if ((pot[j] - o).len2() > r2) {
                    o = (pot[i] + pot[j]) / 2, r2 = (pot[j] - o).len2();
                    for (int k = 0; k < j; k++)
                        if ((pot[k] - o).len2() > r2) o = circle(pot[i], pot[j], pot[k]), r2 = (pot[k] - o).len2();
                }
            }
        }
    }
    return sqrt(r2);
}

