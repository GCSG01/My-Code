#include<bits/stdc++.h>
// #define int long long
using namespace std;
const int N=5e5+5,inf=1e9;
int s,t;
int sum[80];
int siz[80];
int sp[80][80];
int head[N],cur[N],nxt[N],to[N],val[N],tot=1;
int dis[N],fa[N];
void add(int u,int v,int w){
    // cout<<u<<" "<<v<<" "<<w<<"\n";
    nxt[++tot]=head[u],head[u]=tot,to[tot]=v,val[tot]=w;
    nxt[++tot]=head[v],head[v]=tot,to[tot]=u,val[tot]=0;
    return ;
}
int bfs(){
    memset(dis,0,sizeof dis);
    queue<int>q;q.push(s);
    dis[s]=1;
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=head[u];i;i=nxt[i])
            if(val[i]&&!dis[to[i]]){
                dis[to[i]]=dis[u]+1;
				q.push(to[i]);
            }
    }
    return dis[t];
}
int dfs(int x,int lim){
    if(x==t)return lim;
    int f=0;
    for(int &i=cur[x];i;i=nxt[i]){
        if(val[i]&&dis[to[i]]==dis[x]+1){
            int w=dfs(to[i],min(lim-f,val[i]));
            f+=w,val[i]-=w,val[i^1]+=w;
            if(!w)dis[to[i]]=0;
            if(lim==f)break;
        }
    }
    return f;
}
int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n,m,k;cin>>n>>m>>k;
    for(int i=1;i<=n+2;i++)fa[i]=i;
    for(int i=1;i<=m;i++){
        cin>>siz[i]>>sum[i];
        for(int j=1;j<=sum[i];j++){
            cin>>sp[i][j];
            if(!sp[i][j])sp[i][j]=n+1;
            else if(sp[i][j]==-1)sp[i][j]=n+2;
            if(j>1)fa[find(sp[i][j])]=find(sp[i][j-1]);
        }
    }
    if(find(n+1)!=find(n+2))return cout<<0,0;
    s=2e5+1,t=2e5+2;
    int ans=0;
    for(int i=1;;i++){
        add(s,i*(n+1),inf);
        for(int j=1;j<=m;j++){
            int nxt=(i-1)%sum[j]+1;
            int nw=i%sum[j]+1;
            if(sp[j][nxt]==n+2)nxt=t;
            else nxt=(i-1)*(n+1)+sp[j][nxt];
            if(sp[j][nw]==n+2)nw=t;
            else nw=i*(n+1)+sp[j][nw];
            add(nxt,nw,siz[j]);
        }
        while(bfs()){
            memcpy(cur,head,sizeof head);
            ans+=dfs(s,inf);
        }
        // cout<<ans<<"\n";
        if(ans>=k)return cout<<i,0;
        for(int j=1;j<=n+1;j++)
            add((i-1)*(n+1)+j,i*(n+1)+j,inf);
    }
    return 0;
}