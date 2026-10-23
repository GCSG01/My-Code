#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,m,dag[N];
int vis[N],pre[N];
bitset<N>incir;
vector<int>g[N],g2[N],cir,topo;
int c[N],rk[N],id[N];
int mx[N],mn[N];
bool Topo(){
	int tot=0;
	for(int i=1;i<=n;i++)
		tot+=!incir[i];
	for(int i=1;i<=n;i++)
		for(int y:g[i])
			if(!incir[i]&&!incir[y])
				dag[y]++;
	queue<int>q;
	for(int i=1;i<=n;i++)
		if(!incir[i]&&!dag[i])
			q.push(i),topo.push_back(i);
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int y:g[x])
			if(!--dag[y])
				q.push(y),topo.push_back(y);
	}
	return topo.size()==tot;
}
bool dfs(int x){
	vis[x]=1;
	for(int y:g[x]){
		if(vis[y]==2)continue;
		if(vis[y]){
			for(;x!=y;x=pre[x])
				cir.push_back(x);
			cir.push_back(y);
			reverse(cir.begin(),cir.end());
			return true;
		}
		pre[y]=x;
		if(dfs(y))return true;
	}
	vis[x]=2;
	return false;
}
inline void updmn(int &x,int y){
	if(x>y)x=y;
}
inline void updmx(int &x,int y){
	if(x<y)x=y;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++)
		cin>>u>>v,g[u].push_back(v),g2[v].push_back(u);
	for(int i=1;i<=n;i++)
		if(!vis[i]&&dfs(i))break;
	if(!cir.size())
		return cout<<"-1\n",0;
	int tot=0;
	for(int x:cir)incir[x]=1,rk[x]=++tot,id[tot]=x;
	if(!Topo())
		return cout<<"-1\n",0;
	for(int i=1;i<=n;i++)mn[i]=n+1;

	for(int x:cir)
		for(int y:g[x])
			if(!incir[y])
				updmx(mx[y],rk[x]);
	for(int x:topo)
		for(int y:g[x])
			updmx(mx[y],mx[x]);
	for(int x:cir)
		for(int y:g2[x])
			if(!incir[y])
				updmx(mx[x],mx[y]);
	for(int x:cir){
		for(int y:g2[x])
			if(incir[y]&&rk[y]%tot+1!=rk[x])
				updmx(mx[x],rk[y]);
		if(mx[x]>=rk[x])
			c[1]++,c[rk[x]]--;
	}

	reverse(topo.begin(),topo.end());
	for(int i=1;i<=n;i++)mx[i]=0;
	for(int x:cir)
		for(int y:g2[x])
			if(!incir[y])
				updmn(mn[y],rk[x]),updmx(mx[y],rk[x]);
	for(int x:topo)
		for(int y:g2[x])
			updmn(mn[y],mn[x]),updmx(mx[y],mx[x]);
	for(int x:cir)
		for(int y:g[x])
			if(!incir[y])
				updmn(mn[x],mn[y]),updmx(mx[x],mx[y]);
	for(int x:cir){
		for(int y:g[x])
			if(incir[y]&&rk[y]!=rk[x]%tot+1)
				updmn(mn[x],rk[y]),updmx(mx[x],rk[y]);
		if(mn[x]<=rk[x])
			c[rk[x]+1]++;
		else if(mn[x]!=n+1&&mx[x]<=tot)
			c[rk[x]+1]++,c[mx[x]]--;
	}
	// for(int i:cir)cout<<i<<" ";
	// cout<<"\n";
	vector<int>ans;
	for(int i=1;i<=tot;i++)
		if(!(c[i]+=c[i-1]))
			return cout<<cir[i-1],0;
	cout<<"-1";
}