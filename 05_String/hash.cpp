#include <bits/stdc++.h>
using ULL = unsigned long long;

constexpr int MAXN = 1e6 + 7;

const ULL MOD1 = 402653189;
const ULL MOD2 = 805306457;
 
const ULL BASE1 = 13331;
const ULL BASE2 = 23333;
 
ULL p[MAXN][2];
void init()
{
    p[0][0]=p[0][1]=1;
    for(int i=1;i<MAXN;i++) p[i][0]=p[i-1][0]*BASE1%MOD1;
    for(int i=1;i<MAXN;i++) p[i][1]=p[i-1][1]*BASE2%MOD2;
}
struct myHash
{
    ULL h[MAXN][2];
    //  以 1 起点  传0点
    void init(char s[],int n=0)
    {
        n=strlen(s+1),h[n+1][0]=h[n+1][1]=0;
        for(int i=n;i>=1;i--) h[i][0]=(h[i+1][0]*BASE1%MOD1+s[i]-'A'+1)%MOD1;
        for(int i=n;i>=1;i--) h[i][1]=(h[i+1][1]*BASE2%MOD2+s[i]-'A'+1)%MOD2;
    }
    // 注意这里不是传[l, r] 是传  [l, r - l]
    std::pair<ULL,ULL> get_hash(int pos,int length)
    {
        return {
            ((h[pos][0]-h[pos+length][0]*p[length][0]%MOD1)+MOD1)%MOD1,
            ((h[pos][1]-h[pos+length][1]*p[length][1]%MOD2)+MOD2)%MOD2
        };
    }
};