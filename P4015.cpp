#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5,inf=1e9+7;
int a[N],b[N];
int n,m,S,T;
int dis[N],vis[N];
int head[N],cur[N],val[N],to[N],nxt[N],cst[N],tot=1;
void add(int u,int v,int w,int c){
    nxt[++tot]=head[u],head[u]=tot,to[tot]=v,val[tot]=w,cst[tot]=c;
    nxt[++tot]=head[v],head[v]=tot,to[tot]=u,val[tot]=0,cst[tot]=-c;
    return ;
}
int spfa(int fl){
    int fff=0;
    if(fl)memset(dis,0x3f,sizeof dis);
    else memset(dis,-0x3f,sizeof dis);
    fff=dis[S];
    queue<int>q;q.push(S);
    dis[S]=0;
    int tot=0;
    while(!q.empty()){
        int u=q.front();q.pop();
        vis[u]=0;
        tot++;
        // cout<<u<<"\n";
        // if(tot>=6)break;
        for(int i=head[u];i;i=nxt[i])
            if((fl&&val[i]&&dis[to[i]]>dis[u]+cst[i])||
                (!fl&&val[i]&&dis[to[i]]<dis[u]+cst[i])){
                dis[to[i]]=dis[u]+cst[i];
                if(!vis[to[i]])q.push(to[i]),vis[to[i]]=1;
            }
    }
    // for(int i=S;i<=T;i++)
    //     cout<<i<<" "<<dis[i]<<"\n";
    return dis[T]!=fff;
}
int scst=0;
int dfs(int x,int lim){
    if(x==T)return lim;
    int f=0;
    vis[x]=1;
    for(int &i=cur[x];i;i=nxt[i])
        if(!vis[to[i]]&&val[i]&&dis[to[i]]==dis[x]+cst[i]){
            int w=dfs(to[i],min(lim-f,val[i]));
            val[i]-=w,val[i^1]+=w,f+=w,scst+=w*cst[i];
            if(!w)dis[to[i]]=0;
            if(f==lim)break;
        }
    vis[x]=0;
    return f;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>m>>n;
    S=0,T=n+m+1;
    for(int i=1,x;i<=m;i++)cin>>x,add(S,i,x,0);
    for(int i=1,x;i<=n;i++)cin>>x,add(m+i,T,x,0);
    for(int i=1;i<=m;i++)
        for(int j=1,x;j<=n;j++)
            cin>>x,add(i,j+m,inf,x);
    int ans=0;
    // for(int i=S;i<=T;i++)
    //     for(int j=head[i];j;j=nxt[j])
    //         cout<<i<<" "<<to[j]<<" "<<cst[j]<<"\n";
    while(spfa(1)){
        memcpy(cur,head,sizeof head);
        ans+=dfs(S,inf);
    }
    cout<<scst<<"\n",scst=0;
    for(int i=2;i<=tot;i+=2)val[i]+=val[i^1],val[i^1]=0;
    while(spfa(0)){
        memcpy(cur,head,sizeof head);
        ans+=dfs(S,inf);
    }
    cout<<scst;
    return 0;
}