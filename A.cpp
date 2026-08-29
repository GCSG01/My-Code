#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1505,MOD=1e9+7;
int n,q,sz[N]; vector<int> g[N]; vector<ll> dp[N];
ll fac[N],ifac[N];
ll qpow(ll a,ll b){ll r=1;for(;b;b>>=1,a=a*a%MOD)if(b&1)r=r*a%MOD;return r;}
void dfs(int u,int fa){
    vector<ll> p(1,1); int sc=0;
    for(auto it=g[u].begin();it!=g[u].end();it++){
        int v=*it;
		if(v==fa)continue;
        dfs(v,u),sc+=sz[v];
        vector<ll> np(p.size()+dp[v].size()-1);
        for(auto pi=p.begin();pi!=p.end();pi++)
			if(*pi)
				for(auto pj=dp[v].begin();pj!=dp[v].end();pj++)
					if(*pj)
						np[(pi-p.begin())+(pj-dp[v].begin())]=(*(np.begin()+(pi-p.begin())+(pj-dp[v].begin()))+*pi**pj)%MOD;
        p=move(np);
    }
    dp[u].assign(p.size()+1,0);
    for(auto pm=p.begin();pm!=p.end();pm++)
		if(*pm){
			int m=pm-p.begin();
			dp[u][m]=(dp[u][m]+*pm)%MOD;
			dp[u][m+1]=(dp[u][m+1]+*pm*(sc-m))%MOD;
		}
    sz[u]=sc+1;
}
int main(){
	freopen("north.in","r",stdin);
	freopen("north.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0);
    cin>>n>>q;
    for(int i=1,u,v;i<n;i++)
		cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
    fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%MOD;
    ifac[n]=qpow(fac[n],MOD-2);
	for(int i=n;i;i--)ifac[i-1]=ifac[i]*i%MOD;
    dfs(1,0);
    while(q--){
        int x,y;cin>>x>>y;
		ll ans=0;
		int S=sz[x];
        for(auto cm=dp[x].begin()+y;cm!=dp[x].end();cm++)
			if(*cm){
				int m=cm-dp[x].begin();
				ll t=*cm*fac[S-m]%MOD*fac[m]%MOD*ifac[y]%MOD*ifac[m-y]%MOD;
				ans=((m-y)&1)?(ans-t+MOD)%MOD:(ans+t)%MOD;
			}
        cout<<ans<<"\n";
    }
}