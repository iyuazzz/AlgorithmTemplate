// 注意不连通的情况！！！！
#include<bits/stdc++.h>

const int N=3e5+7;
namespace DomTree {
	// N为点数  边数记得无向需要 N * 2
	const int N = 3e5 + 7;
	//  固定成分
	int n, m, tot;
	bool ok = false;
	//  id--dfs序 
	int id[N], rk[N], semi[N], domi[N], mini[N], fa[N], f[N];

	// 灵活成分  如 dfs序  子树siz值 等等(上面已有入度id  所以这里只有out)
	int out[N], siz[N];

	// 图  注意边的大小可能需要二倍
    struct Edge{
        int p[N], v[N], nxt[N], edn;
		void init() {
			for (int i = 1; i <= n; ++ i) {
				p[i] = -1;
			}
			edn = -1;
		}
		// 链式前向星  有向图  
		void add(int u, int to) {
			edn ++;
			v[edn] = to; nxt[edn] = p[u]; p[u] = edn;
		}
        void dfs(int x){
            id[x] = ++tot;
            rk[tot] = x;
            siz[x] = 1;
            for(int i = p[x]; ~i; i = nxt[i]){
                int y = v[i];
                if(id[y]) continue;
                fa[y] = x;
                dfs(y);
                siz[x] += siz[y];
            }
           out[x] = tot;
        }
    }e,fe,sem,dom;

    int fd(int x){
        if(f[x] == x) return x;
        int y = fd(f[x]);
        if(id[semi[mini[f[x]]]] < id[semi[mini[x]]]) mini[x] = mini[f[x]];
        return f[x] = y;
    }
    void tarjan(){
        for(int t = tot; t >= 2; -- t){
            int u = rk[t], mn = n + 1;
            for(int i = fe.p[u]; ~i; i = fe.nxt[i]){
                int v=fe.v[i];
                if(!id[v]) continue;
                fd(v);
                if(id[v]<id[u]) mn = std::min(mn, id[v]);
                else mn = std::min(mn, id[semi[mini[v]]]);
            }
            semi[u] = rk[mn];
            f[u]=fa[u];
            sem.add(semi[u],u);

            u=rk[t-1];
            for(int i = sem.p[u]; ~i; i = sem.nxt[i]){
                int v=sem.v[i]; fd(v);
                if(semi[mini[v]]==semi[v]) domi[v]=semi[v];
                else domi[v]=mini[v];
            }
        }
        for(int i = 2;i <= tot; ++ i){
            int u = rk[i];
            if(domi[u] != semi[u]) domi[u] = domi[domi[u]];
            dom.add(domi[u],u);
        }
    }
    void build() {
		tot = 0;
        e.dfs(1);
		tarjan();
		for (int i = 1; i <= n; ++ i) id[i] = siz[i] = 0;
		tot = 0;
        dom.dfs(1);
    }
    void init(int _n) {
        n = _n;
        for(int i = 1; i <= n; ++ i) {
            semi[i] = domi[i] = mini[i] = f[i] = i;
            id[i] = 0;
        }
        e.init(); fe.init(); sem.init(); dom.init();
    }
    void addedge(int u, int v) {
        e.add(u, v);
        fe.add(v, u);
    }
};
int main () {
    int n, m;
	scanf("%d %d", &n, &m);
	DomTree::init(n);
	while(m --) {
		int u, v;
		scanf("%d %d", &u, &v);
		DomTree::addedge(u, v);
	}
	DomTree::build();
    for (int i = 1; i <= n; ++ i) printf("%d ", DomTree::siz[i]);
	return 0;
}