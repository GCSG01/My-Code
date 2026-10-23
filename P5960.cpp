#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=5e3+5;
int n,m;
vector<pair<int,int>>g[N];
int dis[N],cnt[N],vis[N];
bool SPFA(int st){
	memset(dis,0x3f,sizeof dis);
	queue<int>q;q.push(st),dis[st]=0,vis[st]=1;
	while(q.size()){
		int u=q.front();q.pop();
		vis[u]=0;
		for(auto i:g[u]){
			auto [v,w]=i;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w,cnt[v]=cnt[u]+1;
				if(cnt[v]>=n+1)return 0;
				if(!vis[v])
					q.push(v),vis[v]=1;
			}
		}
	}
	return 1;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1,u,v,w;i<=m;i++)
		cin>>u>>v>>w,g[v].push_back({u,w});
	for(int i=1;i<=n;i++)
		g[0].push_back({i,0});
	if(SPFA(0))
		for(int i=1;i<=n;i++)
			cout<<dis[i]<<" ";
	else cout<<"NO";
}