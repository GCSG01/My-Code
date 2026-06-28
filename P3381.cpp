#include<bits/stdc++.h>
// #define int long long
using namespace std;
const int N=6e5+5,inf=0x3f3f3f3f;
int n,m,s,t;
int head[N],cur[N],nxt[N],to[N],val[N],cst[N],tot;
int dis[N],vis[N];
void add(int u,int v,int w,int c){
    nxt[++tot]=head[u],head[u]=tot,to[tot]=v,val[tot]=w,cst[tot]=c;
    nxt[++tot]=head[v],head[v]=tot,to[tot]=u,val[tot]=0,cst[tot]=-c;
    return ;
}
int spfa(){
    memset(dis,0x3f,sizeof dis);
    memset(vis,0,sizeof vis);
    queue<int>q;q.push(s);
    dis[s]=0,vis[s]=1;
    while(!q.empty()){
        int u=q.front();q.pop();
        vis[u]=0;
        for(int i=head[u];i;i=nxt[i])
            if(val[i]&&dis[to[i]]>dis[u]+cst[i]){
                dis[to[i]]=dis[u]+cst[i];
                if(!vis[to[i]])q.push(to[i]),vis[to[i]]=1;
            }
    }
    return dis[t]<inf;
}
int mincost;
int dinic(int x,int lim){
    if(x==t)return lim;
    int f=0;
    vis[x]=1;
    for(int i=cur[x];i&&lim;i=nxt[i]){
        cur[x]=i;
        int y=to[i];
        if(!vis[y]&&val[i]&&dis[y]==dis[x]+cst[i]){
            int x=dinic(y,min(lim,val[i]));
            val[i]-=x,val[i^1]+=x,lim-=x,f+=x;
            mincost+=x*cst[i];
        }
    }
    vis[x]=0;
    return f;
}
signed main(){
    cin>>n>>m>>s>>t;
    for(int i=1;i<=m;i++){
        int u,v,w,c;cin>>u>>v>>w>>c;
        add(u,v,w,c);
    }
    int ans=0;
    int tot=0;
    while(spfa()){
        memcpy(cur,head,sizeof cur);
        if(tot>=n)break;
        tot++;
        ans+=dinic(s,inf);
    }
    cout<<ans<<" "<<mincost;
    return 0;
}