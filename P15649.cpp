#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+5,mod=998244353;
vector<int>e[N];
int p[N][N],inv[N],f[N][N],g[N],ans;
int siz[N];
int qpow(int x,int y,int s=1){
	for(;y;x*=x,x%=mod,y>>=1)
		if(y&1)s*=x,s%=mod;
	return s;
}
void dfs(int x,int fa){
	siz[x]=1,f[x][0]=1;
	if(e[x].size()==1)return p[x][1]=1,void();
	for(int y:e[x]){
		if(y==fa)continue;
		dfs(y,x),fill(g,g+siz[x]+siz[y]+1,0);
		for(int i=0;i<=siz[x];i++)
			for(int j=1;j<=siz[y];j++)
				g[i+j]+=f[x][i]*p[y][j]%mod,g[i+j]%=mod;
		siz[x]+=siz[y];
		copy(g,g+siz[x]+1,f[x]);
	}
	if(e[x].size()==2){
		int v=e[x][0]!=fa?e[x][0]:e[x][1];
		for(int i=1;i<=siz[v];i++)
			p[x][i+1]=p[v][i];
		return;
	}
	for(int y:e[x]){
		if(y==fa)continue;
		int k=1;
		while(!p[y][k])k++;
		int invp=qpow(p[y][k],mod-2);
		siz[x]-=siz[y];
		int sum=0;
		for(int i=1;i<=siz[x];i++){
			g[i]=f[x][i+k];
			for(int j=min(siz[y],i+k-1);j>k;j--)
				g[i]-=g[i+k-j]*p[y][j]%mod,g[i]%=mod;
			g[i]=g[i]*invp%mod;
			for(int j=1;j<=siz[y];j++){
				int res=g[i]*p[y][j]%mod*inv[i+j]%mod*j;
				sum+=res,p[x][j+1]+=res;
			}
		}
		sum%=mod;
		for(int j=1;j<=siz[y];j++)p[x][j+1]%=mod;
		ans+=siz[y]*(1-sum)%mod,ans%=mod,siz[x]+=siz[y];
	}
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int c,t;cin>>c>>t;
	while(t--){
		int n;cin>>n;
		for(int i=1;i<=n;i++)inv[i]=qpow(i,mod-2);
		for(int i=1;i<=n;i++)e[i].clear();
		for(int i=1;i<=n;i++)fill(f[i],f[i]+n+1,0);
		for(int i=1;i<=n;i++)fill(p[i],p[i]+n+1,0);
		for(int i=1,u,v;i<n;i++)cin>>u>>v,e[u].push_back(v),e[v].push_back(u);
		e[1].push_back(0);
		ans=0,dfs(1,0);
		if(ans<0)ans+=mod;
		cout<<ans<<"\n";
	}
}