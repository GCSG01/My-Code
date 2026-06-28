#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+5,M=5e5+5,inf=1e9;
int head[N],cur[N],nxt[M],to[M],val[M],cst[M],tot=1;
int vis[N],dis[N];
int n,s,t;
int c[N][N];
int ans=0,mincost=0;
void add(int u,int v,int w,int c){
    nxt[++tot]=head[u],head[u]=tot,to[tot]=v,val[tot]=w,cst[tot]=c;
    nxt[++tot]=head[v],head[v]=tot,to[tot]=u,val[tot]=0,cst[tot]=-c;
    return ;
}
int spfa(){
    memset(vis,0,sizeof vis);
    memset(dis,0x3f,sizeof dis);
    queue<int>q;q.push(s);
    dis[s]=0;
    while(!q.empty()){
        int u=q.front();q.pop();
        vis[u]=0;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(val[i]&&dis[v]>dis[u]+cst[i]){
                dis[v]=dis[u]+cst[i];
                if(!vis[v])vis[v]=1,q.push(v);
            }
        }
    }
    memset(vis,0,sizeof vis);
    return dis[t]<inf;
}
int dinic(int x,int lim){
    if(x==t)return lim;
    vis[x]=1;
    int f=0;
    for(int &i=cur[x];i;i=nxt[i]){
        int y=to[i];
        if(!vis[y]&&val[i]&&dis[y]==dis[x]+cst[i]){
            int cnt=dinic(y,min(lim,val[i]));
            val[i]-=cnt,val[i^1]+=cnt,lim-=cnt,f+=cnt;
            mincost+=cnt*cst[i];
            if(!lim)break;
        }
    }
    vis[x]=0;
    return f;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    s=0,t=n*2+1;
    for(int i=1;i<=n;i++)
        add(s,i,1,0),add(i+n,t,1,0);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>c[i][j],add(i,j+n,1,c[i][j]);
    while(spfa()){
        memcpy(cur,head,sizeof head);
        ans+=dinic(s,inf);
    }
    cout<<mincost<<"\n";
    memset(head,0,sizeof head),tot=1;
     for(int i=1;i<=n;i++)
        add(s,i,1,0),add(i+n,t,1,0);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            add(i,j+n,1,-c[i][j]);
    mincost=0;
    while(spfa()){
        memcpy(cur,head,sizeof head);
        ans+=dinic(s,inf);
    }
    cout<<-mincost<<"\n";
    
    return 0;
}