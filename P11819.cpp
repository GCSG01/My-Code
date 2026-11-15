#include<bits/stdc++.h>
using namespace std;
const int N=2e3+5;
int n,m;
int D[N],t[N],d[N],ans;
vector<pair<int,int>>e[N],g[N];
void dij(vector<pair<int,int>>*e,int S,int L,int*s){
	for(int i=1;i<=n;i++)d[i]=s[i]=1e9;
	priority_queue<pair<int,int>>q;
	for(q.push({s[S]=0,S});q.size();){
		int x=q.top().second;q.pop();
		if(d[x]<1e9)continue;
		d[x]=s[x];
		for(auto[i,v]:e[x])
			if((i<=L||x<=L)&&s[i]>v+s[x])
				q.push({-(s[i]=v+s[x]),i});
	}
	for(int i=1;i<=n;i++)
		for(auto[j,v]:e[i])
			s[j]=min(s[j],d[i]+v);
	for(int i=L+1;i<=n;i++)
		for(auto[j,v]:e[i])
			if(j>i)s[j]=min(s[j],s[i]+v);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1,u,v,w;i<=m;i++)
		cin>>u>>v>>w,e[u].push_back({v,w}),g[v].push_back({u,w});
	for(int i=1;i<=n;i++){
		dij(e,i,n,D),dij(e,i,i,t);
		for(int j=i+1;j<=n;j++)
			ans+=t[j]!=D[j];
	}
	for(int i=1;i<=n;i++){
		dij(g,i,n,D),dij(g,i,i,t);
		for(int j=i+1;j<=n;j++)
			ans+=t[j]!=D[j];
	}
	cout<<ans;
}