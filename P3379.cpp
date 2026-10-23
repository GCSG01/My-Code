#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,m,s;
vector<int>g[N];
int fa[N][30],dep[N];
void dfs(int x,int ffa){
	fa[x][0]=ffa,dep[x]=dep[ffa]+1;
	for(int i=1;i<=20;i++)
		fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int y:g[x])
		if(y!=ffa)
			dfs(y,x);
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
    for(int i=20;i>=0;i--)
        if(dep[fa[x][i]]>=dep[y])
            x=fa[x][i];
    if(x==y)return x;
    for(int i=20;i>=0;i--)
        if(fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m>>s;
	for(int i=1,u,v;i<n;i++)
		cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	dfs(s,0);
    while(m--){
        int x,y;cin>>x>>y;
        cout<<LCA(x,y)<<"\n";
    }
}