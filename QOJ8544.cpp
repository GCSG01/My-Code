#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,m;
vector<int>g[N];
int vis[N],flag[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++)vis[i]=flag[i]=0,g[i].clear();
		for(int i=1;i<n;i++)g[i].push_back(i+1),g[i+1].push_back(i);
		g[n].push_back(1);
		for(int i=1,u,v;i<=m;i++)
			cin>>u>>v,u++,v++,g[u].push_back(v),g[v].push_back(u);
		queue<int>q;q.push(1),vis[1]=1;
		while(!q.empty()){
			int x=q.front();q.pop();
			for(int y:g[x])
				if(!vis[y])
					vis[y]=1,flag[y]=flag[x]^1,q.push(y);
		}
		for(int i=1;i<=n;i++)
			cout<<(flag[i]?'R':'B');
		cout<<"\n";
	}
}