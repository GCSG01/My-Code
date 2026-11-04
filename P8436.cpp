//边双
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,m;
vector<pair<int,int>>g[N];
int low[N],dfn[N],tot;
int st[N],top;
vector<vector<int>>ans;
bitset<N>vis;
void tarjan(int x,int id){
	dfn[x]=low[x]=++tot,st[++top]=x,vis[x]=1;
	for(auto [y,c]:g[x])
		if(!dfn[y]&&c!=id)
			tarjan(y,c),low[x]=min(low[x],low[y]);
		else if(vis[y]&&c!=id)low[x]=min(low[x],dfn[y]);
	if(low[x]==dfn[x]){
		vector<int>b;
		while(st[top]!=x)
			vis[st[top]]=0,b.push_back(st[top--]);
		vis[st[top]]=0,b.push_back(st[top--]),ans.push_back(b);
	}
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++)
		cin>>u>>v,g[u].push_back({v,i}),g[v].push_back({u,i});
	for(int i=1;i<=n;i++)
		if(!dfn[i])tarjan(i,0);
	cout<<ans.size()<<"\n";
	for(auto i:ans){
		cout<<i.size();
		for(int j:i)cout<<" "<<j;
		cout<<"\n";
	}
}