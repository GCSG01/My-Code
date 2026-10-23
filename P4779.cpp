#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,m,s;
int dis[N];
bitset<N>vis;
struct node{
	int v,w;
	bool operator<(const node &A)const{
		return w>A.w;
	}
};
vector<node>g[N];
void dij(){
	memset(dis,0x3f,sizeof(dis));
	priority_queue<node>q;
	q.push({s,0}),dis[s]=0;
	while(!q.empty()){
		int u=q.top().v;q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(auto i:g[u])
			if(dis[i.v]>dis[u]+i.w)
				dis[i.v]=dis[u]+i.w,q.push({i.v,dis[i.v]});
	}
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m>>s;
	for(int i=1,u,v,w;i<=m;i++)
		cin>>u>>v>>w,g[u].push_back({v,w});
	dij();
	for(int i=1;i<=n;i++)
		cout<<dis[i]<<" ";
}