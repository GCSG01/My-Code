#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e3+5,mod=1e9+7;
int n,q,sz[N],len[N];
vector<int>g[N];
ll fac[N],inv[N];
ll dp[N][N];
ll qpow(ll x,ll y){
    ll s=1;
    while(y){
        if(y&1)s*=x,s%=mod;
        x*=x,x%=mod,y>>=1;
    }
    return s;
}
void dfs(int u,int fa){
    vector<ll>f(1,1),ff;
    int sum=1,siz=0;
    for(auto v:g[u]){
        if(v==fa)continue;
        dfs(v,u),siz+=sz[v];
        int cnt=sum+len[v]-1;
        ff.assign(cnt,0);
        for(int i=0;i<sum;i++)
            for(int j=0;j<len[v];j++)
                ff[i+j]=(ff[i+j]+f[i]*dp[v][j])%mod;
        f.swap(ff);
        sum=cnt;
    }
    len[u]=sum+1;
    memset(dp[u],0,sizeof(ll)*len[u]);
    for(int i=0;i<sum;i++)
        (dp[u][i]+=f[i])%=mod,(dp[u][i+1]+=f[i]*(siz-i))%=mod;
    sz[u]=siz+1;
}
int main(){
    #ifndef CPH
        freopen("north.in","r",stdin);
        freopen("north.out","w",stdout);
    #endif
    ios::sync_with_stdio(0),cin.tie(0);
    cin>>n>>q;
    for(int i=1,u,v;i<n;i++)
        cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
    fac[0]=1;
    for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=qpow(fac[n],mod-2);
    for(int i=n;i;i--)inv[i-1]=inv[i]*i%mod;
    dfs(1,0);
    while(q--){
        int x,y;cin>>x>>y;
        ll ans=0;
        for(int i=y;i<len[x];i++)
            if(dp[x][i]){
                ll t=dp[x][i]*fac[sz[x]-i]%mod*fac[i]%mod;
                t=t*inv[y]%mod*inv[i-y]%mod;
                if((i-y)&1)ans=(ans-t+mod)%mod;
                else (ans+=t)%=mod;
            }
        cout<<ans<<"\n";
    }
}