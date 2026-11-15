//割点
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,m;
vector<int>g[N];
int dfn[N],low[N],tot;
vector<int>ans;
void tarjan(int x,int root){
	dfn[x]=low[x]=++tot;
	int flag=0;
	for(int y:g[x])
		if(!dfn[y]){
			tarjan(y,root),low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x])flag++;
		}
		else low[x]=min(low[x],dfn[y]);
	if(x!=root&&flag>=1)ans.push_back(x);
	if(x==root&&flag>=2)ans.push_back(x);
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++)
		cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	for(int i=1;i<=n;i++)
		if(!dfn[i])tarjan(i,i);
	sort(ans.begin(),ans.end());
	cout<<ans.size()<<"\n";
	for(int i:ans)cout<<i<<" ";
}