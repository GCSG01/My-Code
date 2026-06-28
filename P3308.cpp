#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,inf=1e9;
int n,s,t;
int a[N],b[N];
struct node{
    int id,c;
}c[N];
int head[N],cur[N],nxt[N],to[N],val[N],tot=1;
int dis[N];
void add(int u,int v,int w){
    nxt[++tot]=head[u],head[u]=tot,to[tot]=v,val[tot]=w;
    nxt[++tot]=head[v],head[v]=tot,to[tot]=u,val[tot]=0;
    return ;
}
int bfs(int ss,int tt){
    memset(dis,0,sizeof dis);
    queue<int>q;q.push(ss);
    dis[ss]=1;
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=head[u];i;i=nxt[i])
            if(val[i]&&!dis[to[i]]){
                dis[to[i]]=dis[u]+1;
                if(to[i]==tt)return 1;
				q.push(to[i]);
            }
    }
    return 0;
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
int dp[N];
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c<='9'&&c>='0')x=x*10+c-'0',c=getchar();
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;rd(T);
    while(T--){
        tot=1;
        memset(head,0,sizeof head);
        rd(n);
        for(int i=1;i<=n;i++)rd(a[i]);
        int mx=0;
        for(int i=1;i<=n;i++){
            dp[i]=1;
            for(int j=1;j<i;j++)
                if(a[j]<a[i])dp[i]=max(dp[i],dp[j]+1);
            mx=max(mx,dp[i]);
        }
        s=0,t=n*2+1;
        for(int i=1,x;i<=n;i++)rd(x),add(i,i+n,x);
        for(int i=1;i<=n;i++){
            if(dp[i]==1)add(s,i,inf);
            if(dp[i]==mx)add(n+i,t,inf);
            for(int j=i+1;j<=n;j++)
                if(a[i]<a[j]&&dp[j]==dp[i]+1)
                    add(n+i,j,inf);
        }
        for(int i=1;i<=n;i++)rd(c[i].c),c[i].id=i;
        sort(c+1,c+n+1,[](node A,node B){
            return A.c<B.c;
        });
        int ans=0;
        while(bfs(s,t)){
            memcpy(cur,head,sizeof head);
            ans+=dfs(s,inf);
        }
        int nt=0;
        for(int i=1;i<=n;i++){
            int u=c[i].id,v=n+u;
            if(bfs(u,v))continue;
            b[++nt]=u,val[u*2]=val[u*2+1]=0;
            for(int j=2;j<=tot;j+=2)
                val[j]+=val[j^1],val[j^1]=0;
            while(bfs(s,t)){
                memcpy(cur,head,sizeof head);
                dfs(s,inf);
            }
        }
        sort(b+1,b+nt+1);
        cout<<ans<<" "<<nt<<"\n";
        for(int i=1;i<=nt;i++)cout<<b[i]<<" ";
        cout<<"\n";
    }
    return 0;
}
