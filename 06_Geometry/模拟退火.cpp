/*
	给定一个N边形所有顶点坐标x,y，求其费马点到所有顶点距离和
	费马点是指到多边形所有顶点距离和最小的点
*/
#include <bits/stdc++.h>
#define RD  (T * (rand() * 2 - RAND_MAX))
// while((double)clock()/CLOCKS_PER_SEC<0.95) SA();   黑科技  直至快tle 才 停止
//  也可以在 SA 中 放一句 if c/c...   < 0.98  return 
// clock()  获取程序运行至今的时间
using namespace std;
const double cold = 0.995; //  单次冷却
const double start = 10000;	//  起始温度
const double eps = 1e-8;	// 精度
const int maxn = 1e2 + 7; // maxn cold  start   三个因素调参  影响时间复杂度  建议每题测一测

struct Point {
	double x, y;
	inline void read() {
		scanf("%lf %lf", &x, &y);
	}
	friend double Dis(const Point& a, const Point& b) {
		return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}
};

vector<Point> P;
int n;
// 计算当前答案
double cal(double x, double y) {
	Point mid = (Point) {x, y};
	double ret = 0;
	for (int i = 0; i < P.size(); ++ i) ret += Dis(mid, P[i]);
	return ret; 
}
// 两行分别为 全局最优解 和  当前退火解
double best, bestx, besty;
double now, nowx, nowy;

void SA() {
	// 每次从当前最优解出发
	now = best; nowx = bestx; nowy = besty;
	for (double T = start; T > eps; T *= cold) {
		double tox = nowx + RD, toy = nowy + RD;
        /*
        	若限定了点的坐标范围  例如必须在 [0, len] 之间  则使用 fmod 函数   fmod(x, mod) 返回 x % mod 的值  （均为浮点数）  
        	注意下列取模  3, 4行的取模  有时 len + eps 需要改成 len
        	if(tox < 0) tox = fmod(tox, len), tox += len;
            if(toy < 0) toy = fmod(toy, len), toy += len;
            if(tox > len) tox = fmod(tox, len + eps);
            if(toy > len) toy = fmod(toy, len + eps);
            
            或者
            
            利用 min max 直接约束随机后的坐标范围
        */
        double toans = cal(tox, toy);
        //  这里取决于取min还是max  改成  < 还是 >
		if(toans < best) {
			best = toans;
			bestx = tox, besty = toy;
		}
		// 关于此处   
		/*
			最大与最小  该如何估价
			设当前答案为 now   随机移动后答案为toans
			则固定 x = now - toans
			如果是求最小解
			则
			if (toans < now || exp(now - toans) * RAND_MAX > rand())
			如果是求最大解
			则
			if (toans > now || exp(now - toans) * RAND_MAX < rand())
		*/
		if(toans < now || exp(now - toans) * RAND_MAX > rand()) {
			now = toans;
			nowx = tox, nowy = toy;
		}
	}
}

void solve () {
	scanf("%d", &n);
	P.resize(n);
	bestx = besty = 0;
	for (int i = 0; i < n; ++ i) P[i].read(), bestx += P[i].x, besty += P[i].y;
	best = cal(bestx /= n, besty /= n);
	
	int tim = 5;
	// 多跑几次
	while(tim --) SA();
	printf("%.0f\n", best);
}

int main () {
	srand(time(NULL));
	int T = 1;
	scanf("%d", &T);
	while(T --) {
		solve ();
		if(T > 0) puts("");
	}
	return 0;
}