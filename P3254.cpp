#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=6e5,inf=1145141919810;
int a[N],b[N];
int n,m,S,T;
int dis[N];
int head[N],cur[N],val[N],to[N],nxt[N],tot=1;
void add(int u,int v,int w){
    nxt[++tot]=head[u],head[u]=tot,to[tot]=v,val[tot]=w;
    nxt[++tot]=head[v],head[v]=tot,to[tot]=u,val[tot]=0;
    return ;
}
int bfs(){
    memset(dis,0,sizeof dis);
    dis[S]=1;queue<int>q;q.push(S);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=head[u];i;i=nxt[i])
            if(val[i]&&!dis[to[i]])
                dis[to[i]]=dis[u]+1,q.push(to[i]);
    }
    return dis[T];
}
int dinic(int x,int y){
    if(x==T)return y;
    int f=0;
    for(int &i=cur[x];i;i=nxt[i])
        if(val[i]&&dis[to[i]]==dis[x]+1){
            int x=dinic(to[i],min(val[i],y-f));
            f+=x,val[i]-=x,val[i^1]+=x;
            if(f==y)break;
        }
    return f;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    S=0,T=n+m+1;
    int sum=0;
    for(int i=1,x;i<=n;i++)cin>>x,add(S,i,x),sum+=x;
    for(int i=1,x;i<=m;i++)cin>>x,add(i+n,T,x);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            add(i,j+n,1);
    /*
    for(int i=1;i<=n+m;i++){
        cout<<i<<": ";
        for(int j=head[i];j;j=nxt[j])
            cout<<to[j]<<" ";
        cout<<"\n";
    }
    */
    int ans=0;
    while(bfs()){
        memcpy(cur,head,sizeof cur);
        ans+=dinic(S,inf);
    }
    if(ans!=sum)return cout<<0,0;
    cout<<1<<"\n";
    for(int i=1;i<=n;i++){
        for(int j=head[i];j;j=nxt[j])
            if(to[j]!=S&&!val[j])cout<<to[j]-n<<" ";
        cout<<"\n";
    }
    return 0;
}