#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,m;
vector<int>g[N];
int vis[N],st[N],top;
int in[N],out[N];
void dfs(int x){
	for(int i=vis[x];i<g[x].size();i=vis[x])
		vis[x]=i+1,dfs(g[x][i]);
	st[++top]=x;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++)
		cin>>u>>v,g[u].push_back(v),in[v]++,out[u]++;
	int flag=0,cnt[2]={0,0},s=1;
	for(int i=1;i<=n;i++)
		if(in[i]!=out[i]){
			flag=1;
			if(out[i]-in[i]==1)cnt[1]++,s=i;
			else if(in[i]-out[i]==1)cnt[0]++;
			else return cout<<"No",0;
		}
	if(flag&&(cnt[0]!=1||cnt[1]!=1))return cout<<"No",0;
	for(int i=1;i<=n;i++)sort(g[i].begin(),g[i].end());
	dfs(s);
	while(top)cout<<st[top--]<<" ";
}