#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,m;
vector<int>g[N],a[N];
int vis[N],deg[N],ans[N];
queue<int>q;
int solve(){
	int cnt=0;
	while(!q.empty()){
		int x=q.front();q.pop();
		cnt++;
		if(deg[x]!=1){
			if(deg[x]<1)return x;
			for(int i=1;i<=n;i++)cout<<"0\n";
			exit(0);
		}
		cnt+=g[x].size()+a[x].size();
		for(auto y:g[x])
			if(--deg[y]==1)q.push(y);
		for(int y:a[x])
			if(--deg[y]==1)q.push(y);
	}
	for(int i=1;i<=n;i++)cout<<"0\n";
	exit(0);
}
void dfs(int x,int fa){
	ans[x]=1;
	for(int y:g[x])
		if(y!=fa&&!vis[y])
			dfs(y,x);
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1,u,v;i<n;i++)cin>>u>>v,g[u].push_back(v),g[v].push_back(u),deg[u]++,deg[v]++;
	for(int i=1,u,v;i<=m;i++)cin>>u>>v,a[u].push_back(v),deg[v]++,vis[u]=1;
	for(int i=1;i<=n;i++)
		if(deg[i]==1)q.push(i);
	dfs(solve(),0);
	for(int i=1;i<=n;i++)cout<<ans[i]<<"\n";
}