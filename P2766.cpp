#include<bits/stdc++.h>
using namespace std;
const int N=3e4+5,inf=1e9+7;
int n,s,t;
int a[N],dp[N];
int head[N],cur[N],nxt[N],to[N],val[N],tot=1;
int dis[N];
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
            if(val[i]&&!dis[to[i]])
                dis[to[i]]=dis[u]+1,q.push(to[i]);
    }
    return dis[t];
}
int dfs(int x,int lim){
    if(x==t)return lim;
    int f=0;
    for(int i=cur[x];i;i=nxt[i]){
        cur[x]=i;
        if(val[i]&&dis[to[i]]==dis[x]+1){
            int w=dfs(to[i],min(lim-f,val[i]));
            f+=w,lim-=w,val[i]-=w,val[i^1]+=w;
            if(!lim)break;
        }
    }
    return f;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)
        for(int j=i-1;j>=0;j--)
            if(a[j]<=a[i])dp[i]=max(dp[i],dp[j]+1);
    int sum=0;
    for(int i=1;i<=n;i++)
        sum=max(sum,dp[i]);
    cout<<sum<<"\n";
    s=0,t=n+n+1;
    for(int i=1;i<=n;i++){
        add(i,n+i,1);
        if(dp[i]==sum)add(n+i,t,1);
        if(dp[i]==1)add(s,i,1);
        for(int j=1;j<i;j++)
            if(dp[i]==dp[j]+1&&a[j]<=a[i])add(j+n,i,1);
    }
    int ans=0;
    while(bfs()){
        memcpy(cur,head,sizeof head);
        ans+=dfs(s,inf);
    }
    cout<<ans<<"\n";
    add(1,n+1,inf),add(s,1,inf);
    if(dp[n]==sum)add(n,n+n,inf),add(n+n,t,inf);
    while(bfs()){
        memcpy(cur,head,sizeof head);
        ans+=dfs(s,inf);
    }
    if(ans>inf)ans=1;
    cout<<ans;
    return 0;
}