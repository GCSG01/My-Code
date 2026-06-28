#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
const int N=1e6+5,M=1e6+5;
struct edge{
    int u,v,w,a;
}e[N];
struct node{
    int v,w;
};
vector<node>a[N];
vector<int>g[N];
int f[N],fa[N][30];
int val[N],dis[N];
int vis[N];
int Ans[N];
int deep[N];
int n,m,tot;
int find(int x){
    return f[x]==x?x:f[x]=find(f[x]);
}
void kru(){
    sort(e+1,e+m+1,[](edge A,edge B){
        return A.a>B.a;
    });
    for(int i=1;i<=n*2;i++)f[i]=i;
    for(int i=1;i<=m;i++){
        int u=e[i].u,v=e[i].v;
        u=find(u),v=find(v);
        if(u==v)continue;
        f[u]=f[v]=++tot;
        val[tot]=e[i].a;
        g[tot].push_back(u);
        g[tot].push_back(v);
    }
    return ;
}
void Dij(){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
    q.push({0,1}),dis[1]=0;
    while(!q.empty()){
        auto now=q.top();q.pop();
        if(now.first>dis[now.second])continue;
        for(auto y:a[now.second])
            if(dis[y.v]>now.first+y.w)
                dis[y.v]=now.first+y.w,q.push({dis[y.v],y.v});
    }
    return ;
}
void dfs(int x,int ffa){
    //Ans[x]=dis[x];
    if(g[x].size()<=1) Ans[x]=dis[x];
    else Ans[x]=LLONG_MAX;
    fa[x][0]=ffa,deep[x]=deep[ffa]+1;
    for(int i=1;i<=25;i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    for(auto i:g[x])
        dfs(i,x),Ans[x]=min(Ans[x],Ans[i]);
    return ;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        cin>>n>>m,tot=n;
        memset(Ans,0x3f,sizeof Ans);
        memset(dis,0x3f,sizeof dis);
        memset(fa,0,sizeof fa);
        for(int i=1;i<=n;i++)
            a[i].clear();
        for(int i=1;i<=n*2;i++)
            g[i].clear();
        for(int i=1;i<=m;i++){
            int u,v,w,aa;
            cin>>u>>v>>w>>aa;
            e[i]={u,v,w,aa};
            a[u].push_back({v,w});
            a[v].push_back({u,w});
        }
        int q,k,s;cin>>q>>k>>s;
        int lst=0;
        kru();
        Dij();
        dfs(tot,tot);
        while(q--){
            int v,p;cin>>v>>p;
            v+=k*lst-1,v%=n,v++;
            p+=k*lst,p%=s+1;
           // cout<<v<<" "<<p<<"\n";
            for(int i=25;i>=0;i--)
                if(deep[v]>(1<<i)&&val[fa[v][i]]>p)
                    v=fa[v][i];
           // cout<<v<<" ";
            cout<<Ans[v]<<"\n",
            lst=Ans[v];
        }
    }
    return 0;
}