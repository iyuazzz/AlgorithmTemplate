#ifdef iyua
    #include "iyua.h"
#endif 

struct DSU {
    std::vector<int> parent, siz;
    DSU(int n) : parent(n + 1), siz(n + 1, 1) {
        std::iota(parent.begin(), parent.end(), 0);
    }
    int root(int x) {return x == parent[x] ? x : (parent[x] = root(parent[x]));}
    bool same(int x, int y) {return root(x) == root(y);}
    bool line(int x, int y) {
        int fx = root(x), fy = root(y);
        if(fx == fy) return false;
        parent[fy] = fx;
        siz[fx] += siz[fy];
        return true;
    }
};