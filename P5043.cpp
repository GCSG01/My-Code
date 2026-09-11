#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
using namespace std;
const int N=55;
const ull C=1e9+7;
int m;
ull h1[N],h2[N];
map<ull,int>t;
vector<int>g[N];
inline ull F(ull x){
    x^=x>>23;
    x*=0x2127599bf4325c37ULL;
    x^=x>>47;
    return x;
}
void dfs(int x,int fa){
    h1[x]=13;
    for(int y:g[x])
        if(y!=fa)
            dfs(y,x),h1[x]+=F(h1[y]);
}
void dp(int x,int fa){
    h2[x]=h1[x];
    if(fa)h2[x]+=F(h2[fa]-F(h1[x]));
    for(int y:g[x])
        if(y!=fa)
            dp(y,x);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>m;
    for(int i=1;i<=m;i++){
        int n;cin>>n;
        for(int j=1;j<=n;j++)g[j].clear();
        int rt=1;
        for(int j=1,x;j<=n;j++){
            cin>>x;
            if(x)g[j].push_back(x),g[x].push_back(j);
            else rt=j;
        }
        dfs(rt,0),dp(rt,0);
        ull ans=h2[1];
        for(int j=2;j<=n;j++)
            ans=min(ans,h2[j]);
        if(!t.count(ans))t[ans]=i;
        cout<<t[ans]<<"\n";
    }
}