//点双
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,m;
vector<int>g[N];
int dfn[N],low[N],tot;
int st[N],top;
bitset<N>vis;
vector<vector<int>>ans;
void tarjan(int x){
	dfn[x]=low[x]=++tot,st[++top]=x;
	for(int y:g[x])
		if(!dfn[y]){
			tarjan(y),low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]){
				vector<int>b;
				while(st[top]!=y)
					b.push_back(st[top--]);
				b.push_back(st[top--]),b.push_back(x);
				ans.push_back(b);
			}
		}
		else low[x]=min(low[x],dfn[y]);
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++)
		cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);
	for(auto &i:ans){
		sort(i.begin(),i.end());
		for(int j:i)vis[j]=1;
	}
	for(int i=1;i<=n;i++)
		if(!vis[i])ans.push_back({i});
	cout<<ans.size()<<"\n";
	for(auto i:ans){
		cout<<i.size()<<" ";
		for(int j:i)cout<<j<<" ";
		cout<<"\n";
	}
}