//强连通分量
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,m;
int p[N];
vector<int>g[N],G[N];
int dfn[N],low[N],tot=0;
bitset<N>vis;
int st[N],top,fa[N];
int scc[N],sz[N],scctot;
int val[N],dp[N],deg[N];
void tarjan(int x){
	dfn[x]=low[x]=++tot,st[++top]=x,vis[x]=1;
	for(int y:g[x])
		if(!dfn[y])
			tarjan(y),low[x]=min(low[x],low[y]);
		else if(vis[y])low[x]=min(low[x],dfn[y]);
	if(dfn[x]==low[x]){
		++scctot;
		do{
			scc[st[top]]=scctot,sz[scctot]++;
			vis[st[top]]=0;
		}while(st[top--]!=x);
	}
}
int topo(int n=scctot){
	queue<int>q;
	for(int i=1;i<=n;i++)
		if(!deg[i])q.push(i);
	for(int i=1;i<=n;i++)dp[i]=val[i];
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int y:G[x]){
			dp[y]=max(dp[y],val[y]+dp[x]);
			if(!--deg[y])q.push(y);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)ans=max(ans,dp[i]);
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>p[i];
	for(int i=1,u,v;i<=m;i++)
		cin>>u>>v,g[u].push_back(v);
	for(int i=1;i<=n;i++)
		if(!dfn[i])tarjan(i);
	for(int i=1;i<=n;i++)
		if(!scc[i])scc[i]=++scctot;
	for(int i=1;i<=n;i++){
		val[scc[i]]+=p[i];
		for(int y:g[i])
			if(scc[i]!=scc[y])
				G[scc[i]].push_back(scc[y]),deg[scc[y]]++;
	}
	cout<<topo();
}