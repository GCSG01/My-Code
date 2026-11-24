#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int n,m,k;
unordered_map<int,int>e[N];
queue<array<int,2>>q;
int fa[N];
int cnt[N];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y)return;
	if(e[x].size()<e[y].size())swap(x,y);
	for(auto [u,v]:e[y])
		if(e[x].count(u))
			q.push({e[x][u],v});
		else e[x][u]=v;
	fa[y]=x,e[y].clear();
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1,u,v,w;i<=m;i++){
		cin>>u>>v>>w,swap(u,v);
		if(e[u].count(w))
			q.push({e[u][w],v});
		else e[u][w]=v;
	}
	while(!q.empty()){
		auto x=q.front();q.pop();
		merge(x[0],x[1]);
	}
	for(int i=1;i<=n;i++)cnt[find(i)]++;
	int ans=0;
	for(int i=1;i<=n;i++)
		ans+=cnt[i]*(cnt[i]-1)/2;
	cout<<ans;
}