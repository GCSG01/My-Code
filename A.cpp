#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+5,mod=1e9+7;
int n;
vector<int>g[N];
int mx[N];
int f[N][N];
void init(int x,int fa){
	mx[x]=x;
	for(int y:g[x])
		if(y!=fa)init(y,x),mx[x]=max(mx[x],mx[y]);
}
void dfs(int x,int fa){
	sort(g[x].begin(),g[x].end(),[](int A,int B){return mx[A]>mx[B];});
	int flag=0;
	for(int y:g[x])
		if(y!=fa){
			dfs(y,x);
			for(int i=0;i<mx[y];i++)
				if(flag)
					f[x][i]=(f[x][i]+f[y][i]*f[x][mx[y]]%mod)%mod;
				else f[x][i]=f[y][i]*f[x][mx[y]]%mod;
			flag=1;
		}
	for(int i=0;i<x;i++)f[x][i]=f[x][x];
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	freopen("dfs.in","r",stdin);
	freopen("dfs.out","w",stdout);
	int id,o,t;cin>>id>>o>>t;
	while(t--){
		int rt;cin>>n>>rt;
		for(int i=1;i<=n;i++)g[i].clear();
		for(int i=1,u,v;i<n;i++)cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
		for(int i=1;i<=n;i++)
			for(int j=0;j<=n;j++)
				f[i][j]=1;
		init(rt,0),dfs(rt,0);
		if(o==1)
			cout<<f[rt][0]<<"\n";
		else{
			for(int i=1;i<=n;i++)
				cout<<f[i][0]<<" ";
			cout<<"\n";
		}
	}
}