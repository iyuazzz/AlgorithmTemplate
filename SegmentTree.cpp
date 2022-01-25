#ifdef iyua
    #include "iyua.h"
#endif

template <class Info, class Merge = std::plus<Info> >
struct SegmentTree {
    /*
        base [1, n]
        1. recompose the Info class
        2. std::vector<Info> vec(n),  then assign the value of vec
        3. SegmentTree<Info> tree(vec);
    */
    const int n;
    const Merge merge;
    std::vector<Info> info;
    SegmentTree(int _n) : n(_n), merge(Merge()), info(4 * (_n + 1)) {}
    SegmentTree(std::vector<Info> init) : SegmentTree(init.size()) {
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if(l == r) {
                info[p] = init[l - 1];
                return ;
            }
            int m = (l + r) >> 1;
            build(p * 2, l, m);
            build(p * 2 + 1, m + 1, r);
            pull(p);
        };
        build(1, 1, n);
    };
    inline void pull(int p) {
        info[p] = merge(info[p * 2], info[p * 2 + 1]);
    }
    void modify(int p, int l, int r, int x, const Info& v) {
        if(l == r) {
            info[p] = v;
            return ;
        }
        int m = (l + r) >> 1;
        if(x <= m) {
            modify(p * 2, l, m, x, v);
        } else {
            modify(p * 2 + 1, m + 1, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info& v) {
        modify(1, 1, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if(y < l || r < x) {
            return Info();
        }
        if(x <= l && r <= y) {
            return info[p];
        }
        int m = (l + r) >> 1;
        return merge(rangeQuery(p * 2, l, m, x, y), rangeQuery(p * 2 + 1, m + 1, r, x, y));
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 1, n, l, r);
    }
};
struct Info {
    int val;
    Info(int v = 0) : val(v) {}
    inline void readin() {}
    friend Info operator + (const Info& l, const Info& r) {
        return Info(l.val + r.val);
    }
};
