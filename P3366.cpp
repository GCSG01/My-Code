#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
struct node{
	int u,v,w;
}e[N];
int fa[N];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,m;cin>>n>>m;
	for(int i=1;i<=m;i++)
		cin>>e[i].u>>e[i].v>>e[i].w;
	sort(e+1,e+m+1,[](node A,node B){return A.w<B.w;});
	int ans=0,cnt=n;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		int u=find(e[i].u),v=find(e[i].v);
		if(u!=v)
			fa[u]=v,ans+=e[i].w,cnt--;
	}
	if(cnt>1)cout<<"orz";
	else cout<<ans;
}