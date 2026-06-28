#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
const int N=3e4+5,M=5e4+5;
struct node{
    int v,w;
};
vector<node>g[N],a[N];
int n,m,q;
int dfn[N],low[N],tot;
int Fa[N][18],deep[N],dis[N];
int val[N],fa[N];
int sum[N],etot=n;
void solve(int u,int v,int w){
    int pre=w,i=v;
    while(i!=fa[u])
        sum[i]=pre,pre+=val[i],i=fa[i];
    sum[++etot]=sum[u],sum[u]=0;
    i=v;
    while(i!=fa[u]){
        int cnt=min(sum[i],sum[etot]-sum[i]);
        a[etot].push_back({i,cnt});
        a[i].push_back({etot,cnt});
        i=fa[i];
    }
    return ;
}
void tarjan(int x,int ffa){
    dfn[x]=low[x]=++tot;
    for(auto i:g[x])
        if(i.v!=ffa){
            if(!dfn[i.v]){
                fa[i.v]=x,val[i.v]=i.w;
                tarjan(i.v,x);
                low[x]=min(low[x],low[i.v]);
            }
            else low[x]=min(low[x],dfn[i.v]);
            if(low[i.v]>dfn[x])
                a[x].push_back({i.v,i.w}),
                a[i.v].push_back({x,i.w});
        }
    for(auto i:g[x])
        if(fa[i.v]!=x&&dfn[i.v]>dfn[x])
            solve(x,i.v,i.w);
    return ;
}
void dfs(int x,int ffa){
    Fa[x][0]=ffa,deep[x]=deep[ffa]+1;
    for(int i=1;i<=14;i++)
        Fa[x][i]=Fa[Fa[x][i-1]][i-1];
    for(auto i:a[x])
        if(i.v!=ffa)
            dis[i.v]=dis[x]+i.w,dfs(i.v,x);
    return ;
}
pair<int,int> LCA(int u,int v){
    if(deep[u]<deep[v])swap(u,v);
    for(int i=14;i>=0;i--)
        if(deep[Fa[u][i]]>=deep[v])
            u=Fa[u][i];
    if(u==v)return {u,-1};
    for(int i=14;i>=0;i--)
        if(Fa[u][i]!=Fa[v][i])
            u=Fa[u][i],v=Fa[v][i];
    return {u,v};
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    rd(n),rd(m),rd(q);
    etot=n;
    for(int i=1;i<=m;i++){
        int u,v,w;rd(u),rd(v),rd(w);
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    tarjan(1,0);
    dfs(1,0);
    while(q--){
        int u,v;rd(u),rd(v);
        auto tmp=LCA(u,v);
        int fu=tmp.first,fv=tmp.second;
        int p=Fa[fu][0],ans=0;
        if(fv==-1)p=fu;
        if(p<=n)ans=dis[u]+dis[v]-dis[p]*2;
        else{
            ans=dis[u]+dis[v]-dis[fu]-dis[fv];
            if(sum[fu]<sum[fv])swap(fu,fv);
            ans+=min(sum[fu]-sum[fv],sum[p]+sum[fv]-sum[fu]);
        }
        cout<<ans<<"\n";
    }
    return 0;
}