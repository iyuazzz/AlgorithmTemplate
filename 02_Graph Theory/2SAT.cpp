#include <bits/stdc++.h>

constexpr int maxn = 1e6 + 7;
/*
    O(n + m)
    1~n  false      0   不选
    n+1~n+n true    1   选
    连边(a, b)含义   若选a必选b
    根据题目给出性质，自行推出主析取范式
    给出几个基础变换  -x 表示非x
    若a则b              a -> b   -b -> -a
    a, b至少满足一个     -a -> b   -b -> a
    a必定满足           -a -> a (即某个状态必定成立就把相对状态指向它)
    a b 不共存			 a -> -b    b -> -a
    
    a b 不相同   
    		a -> b + n	 b -> a + n
    		a + n -> b	 b + n -> a
    
    a b 相同	   
    
    		a -> b   a + n -> b + n
    		b -> a	 b + n -> a + n
    可以利用一个宏  简洁快速算出这个点对应的点
    例如  #define near(x)		((x > n) ? x - n : x + n)
    
    前缀建图 2-sat
	对于一个集合内所有点只能选一个的情况， 朴素办法是 n^2 连边
	我们可以用前缀来优化这个建图， 额外开个 pre 数组，  对于每个·1集合
	设 x_1 为当前选  x_0为当前不选  prex_0 为 1 ~ x 不选 prex_1 为选
	设 y 为集合内 x 前面一个  同上
	则
	
	prex_0 -> x_0
	x_1  ->  prex_1
    
    prey_1 -> x_0
	x_1  ->  prey_0	

	prex_0  ->  prey_0
	prey_1  ->  prex_1
*/
struct Two_Sat {
    int n, scc[maxn], dfn[maxn], low[maxn];
    int scc_cnt, tim;
    bool insta[maxn];
    std::stack<int> sta;
    std::vector<int> G[maxn]; // 二倍n
    void init(int num) {
        n = num;
        scc_cnt = tim = 0;
        for (int i = 0; i <= n + n; ++ i) {
            G[i].clear();
            scc[i] = dfn[i] = low[i] = 0;
            insta[i] = 0;
        }
        while(sta.size()) sta.pop();
    }
    // 代表从a向b连边
    inline void add(int a, int b) {
        G[a].push_back(b);
    }
    void Tarjan(int u) {
        dfn[u] = low[u] = ++ tim;
        sta.push(u); insta[u] = true;
        for (int i = 0; i < G[u].size(); ++ i) {
            int v = G[u][i];
            if(!dfn[v]) {
                Tarjan(v);
                low[u] = std::min(low[u], low[v]);
            } else if(insta[v]) low[u] = std::min(low[u], dfn[v]);
        }
        if(dfn[u] == low[u]) {
            ++ scc_cnt; int v;
            do {
                v = sta.top(); sta.pop();
                insta[v] = false; scc[v] = scc_cnt;
            } while(v != u);
        }
    }
    bool twosat() {
        for (int i = 1; i <= n + n; ++ i) {
            if(!dfn[i]) Tarjan(i);
        }
        for (int i = 1; i <= n; ++ i) {
            if(scc[i] == scc[i + n]) {
                return false;
            }
        }
        return true;
    }
    //  1~i 表示不选
    //  考虑 -a -> b -> a这种情况
    //  输出方案时 优先输出拓扑序大的就可以避免
    //  scc编号是逆拓扑序  所以优先输出小的scc编号
    void WriteAns() {
        for (int i = 1; i <= n; ++ i) {
            if(scc[i] < scc[i + n]) {
                printf("0 ");
            } else {
                printf("1 ");
            }
        }
        puts("");
    }
};