#include<bits/stdc++.h>
// #define int long long
using namespace std;
const int N=3e5+5,M=2e6+5;
int n,m,f[N],fa[N][30],dep[N],val[N];
struct Edge{
    int u,v,w;
}e[M];
vector<int>g[M];
int tot;
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
void Kru(){
    for(int i=1;i<=n*2;i++)f[i]=i;
    sort(e+1,e+m+1,[](Edge A,Edge B){return A.w<B.w;});
    for(int i=1;i<=m;i++){
        auto [u,v,w]=e[i];
        u=find(u),v=find(v);
        if(u==v)continue;
        val[++tot]=w,f[u]=f[v]=tot;
        g[tot].push_back(v),g[tot].push_back(u);
    }
    return ;
}
void dfs(int x,int ffa){
    fa[x][0]=ffa,dep[x]=dep[ffa]+1;
    for(int i=1;i<=22;i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    for(auto y:g[x])dfs(y,x);
    return ;
}
int LCA(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    for(int i=22;i>=0;i--)
        if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
    if(x==y)return x;
    for(int i=22;i>=0;i--)
        if(fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int q,M;cin>>n>>M>>q,tot=n;
    for(int i=1;i<=M;i++)
        for(int j=M-i+1;j+M-i+1<=n;j+=M-i+1)
            e[++m]={j,j+M-i+1,i};
    Kru();
    for(int i=tot;i>=1;i--)
        if(!dep[i])
            dfs(i,0);
    while(q--){
        int x,y;cin>>x>>y;
        cout<<val[LCA(x,y)]<<"\n";
    }
    return 0;
}