#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5,mod=998244353;
int n;
struct DSU{
	int fa[N],d[N],val[N],dep[N];
	inline int find(int x){
		if(fa[x]==x)return x;
		int p=fa[x];
		fa[x]=find(fa[x]);
		d[x]+=d[p],d[x]%=mod;
		return fa[x];
	}
	inline void init(){
		for(int i=1;i<=n;i++)fa[i]=i,d[i]=dep[i]=val[i]=0;
	}
	inline void update(int x,int k){
		val[x]=k;
	}
	inline void add(int x,int k){
		(val[find(x)]+=k)%=mod;
	}
	inline int query(int x){
		int p=find(x);
		return (d[x]+val[p])%mod;
	}
	inline void merge(int x,int y){
		x=find(x),y=find(y);
		if(x==y)return ;
		if(dep[x]<dep[y])swap(x,y);
		fa[y]=x;
		if(dep[x]==dep[y])dep[x]++;
		d[y]=(val[y]-val[x])%mod;
	}
}dsu;
int val[N],p[N];
vector<int>g[N];
int fat[N];
bitset<N>vis;
void init(int x,int ffa){
	fat[x]=ffa;
	for(int y:g[x])
		if(y!=ffa)
			init(y,x),val[x]+=val[y],val[x]%=mod;
}
void clear(){
	for(int i=1;i<=n;i++)g[i].clear(),vis[i]=0,val[i]=0;
}
void solve(){
	cin>>n,clear();
	for(int i=1,u,v;i<n;i++)
		cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	for(int i=1;i<=n;i++)cin>>val[i];
	init(1,0),dsu.init();
	for(int i=1;i<=n;i++)cin>>p[i];
	for(int i=n;i>=1;i--){
		int x=p[i];vis[x]=1;
		for(int y:g[x])
			if(!vis[y]);
			else if(y==fat[x])dsu.add(y,val[x]);
			else dsu.add(y,val[1]-val[y]);
		dsu.update(x,val[1]);
		for(int y:g[x])
			if(vis[y])dsu.merge(x,y);
	}
	for(int i=1;i<=n;i++)
		cout<<(dsu.query(i)+mod)%mod<<" ";
	cout<<"\n";
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	while(T--)solve();
}