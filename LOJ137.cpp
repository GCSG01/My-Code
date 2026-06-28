#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5,M=3e5+5,p=1e9+7;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
struct edge{
    int u,v,w;
}e[M];
vector<int>g[N];
int fa[N][20];
int st[N][20];
int val[N];
int f[N],tot;
int deep[N],dis[N];
int n,m;
int A,B,C,P;
inline int rnd(){
    return A=(A*B+C)%P;
}
inline int find(int x){
    return x==f[x]?x:f[x]=find(f[x]);
}
void Kru(){
    sort(e+1,e+m+1,[](edge A,edge B){
        return A.w<B.w;
    });
    int cnt=0;
    for(int i=1;i<=m;i++){
        int u=e[i].u,v=e[i].v;
        u=find(u),v=find(v);
        if(u==v)continue;
        f[u]=f[v]=++tot;
        val[tot]=e[i].w;
        g[tot].push_back(v);
        g[tot].push_back(u);
        cnt++;
        if(cnt==n-1)break;
    }
    return ;
}
void dfs(int x,int ffa){
    fa[x][0]=ffa,deep[x]=deep[ffa]+1;
    for(int i=1;i<=18;i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    for(auto i:g[x])
        if(i!=ffa)
            dfs(i,x);
    return ;
}
int LCA(int x,int y){
    if(x==y)return x;
    if(deep[x]<deep[y])swap(x,y);
    for(int i=18;i>=0;i--)
        if(deep[fa[x][i]]>=deep[y])
            x=fa[x][i];
    if(x==y)return x;
    for(int i=18;i>=0;i--)
        if(fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    tot=n;
    for(int i=1;i<=m;i++)
        cin>>e[i].u>>e[i].v>>e[i].w;
    for(int i=1;i<=n*2;i++)f[i]=i;
    Kru();
    dfs(tot,0);
    int q,ans=0;
    cin>>q>>A>>B>>C>>P;
    while(q--){
        int u=rnd()%n+1,v=rnd()%n+1;
        ans+=val[LCA(u,v)],ans%=p;
    }
    cout<<ans;
    return 0;
}