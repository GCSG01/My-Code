#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5,M=3e5+5;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
struct edge{
    int u,v,w;
}e[M];
vector<int>g[N];
int st[N][20];
int val[N];
int f[N],tot;
int deep[N],que[N],dfn[N],idx;
int lg[N];
int n,m,q;
inline int find(int x){
    return x==f[x]?x:f[x]=find(f[x]);
}
void Kru(){
    sort(e+1,e+m+1,[](edge A,edge B){
        return A.w<B.w;
    });
    for(int i=1;i<=m;i++){
        int u=e[i].u,v=e[i].v;
        u=find(u),v=find(v);
        if(u==v)continue;
        f[u]=f[v]=++tot;
        val[tot]=e[i].w;
        g[tot].push_back(v);
        g[tot].push_back(u);
    }
    return ;
}
void dfs(int x,int ffa){
    deep[x]=deep[ffa]+1,dfn[x]=++idx,que[idx]=x;
    for(auto i:g[x])
        if(i!=ffa)
            dfs(i,x),que[++idx]=x;
    return ;
}
void init(){
    for(int i=1;i<=idx;i++)
        st[i][0]=que[i];
    for(int i=1;i<=18;i++)
        for(int j=1;j+(1<<i)<=idx;j++){
            int x=st[j][i-1],y=st[j+(1<<(i-1))][i-1];
            st[j][i]=deep[x]<deep[y]?x:y;
        }
    lg[0]=-1;
    for(int i=1;i<=idx;i++)
        lg[i]=lg[i>>1]+1;
    return ;
}
int LCA(int x,int y){
    if(x==y)return x;
    x=dfn[x],y=dfn[y];
    if(x>y)swap(x,y);
    int k=lg[y-x+1],xx=st[x][k],yy=st[y-(1<<k)+1][k];
    return deep[xx]<deep[yy]?xx:yy;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>q;
    tot=n;
    for(int i=1;i<=m;i++)
        cin>>e[i].u>>e[i].v>>e[i].w;
    for(int i=1;i<=n*2;i++)f[i]=i;
    Kru();
    for(int i=1;i<=tot;i++)
        if(!deep[i])
            dfs(find(i),0);
    init();
    while(q--){
        int u,v;cin>>u>>v;
        if(find(u)!=find(v))cout<<"-1\n";
        else cout<<val[LCA(u,v)]<<"\n";
    }
    return 0;
}