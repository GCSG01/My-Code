#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m;
vector<int>e[N],a[N];
int dfn[N],low[N],val[N],idx;
int st[N],top,tot,ans;
int siz[N],SUM;
void tarjan(int x,int ffa){
    dfn[x]=low[x]=++idx,SUM++;
    val[x]=-1,st[++top]=x;
    for(auto y:e[x])
        if(y!=ffa){
            if(!dfn[y]){
                tarjan(y,x);
                low[x]=min(low[x],low[y]);
                if(low[y]>=dfn[x]){
                    tot++,a[x].push_back(tot),a[tot].push_back(x),val[tot]++;
                    int now;
                    do{
                        now=st[top--],a[now].push_back(tot),a[tot].push_back(now),val[tot]++;
                    }while(now!=y);
                }
            }
            else low[x]=min(low[x],dfn[y]);
        }
    return ;
}
void dfs(int x,int ffa){
    siz[x]=x<=n;
    for(int y:a[x])
        if(y!=ffa){
            dfs(y,x),
            ans+=2*siz[x]*siz[y]*val[x];
            siz[x]+=siz[y];
        }
    ans+=2*siz[x]*(SUM-siz[x])*val[x];
    return ;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m,tot=n;
    for(int i=1,u,v;i<=m;i++)
        cin>>u>>v,e[u].push_back(v),e[v].push_back(u);
    for(int i=1;i<=n;i++)
        if(!dfn[i])SUM=0,tarjan(i,0),dfs(i,0);
    cout<<ans;
    return 0;
}