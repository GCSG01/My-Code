#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=250005;
struct node{
	int v,w;
};
int n,u,v,w,q,k;
int h[N],dep[N],fa[N][23],l[N][23];
int dp[N],st[N],top,dfn[N],tot;
vector<node>ed[N];
bool vis[N];
void dfs(int u,int f){
	fa[u][0]=f,dep[u]=dep[f]+1,dfn[u]=++tot;
	for(auto i:ed[u])
		if(i.v!=f)
			l[i.v][0]=i.w,dfs(i.v,u);
	return ;
}
int LCA(int a,int b){
	if(dep[a]<dep[b])
		swap(a,b);
	int k=dep[a]-dep[b];
	for(int i=18;i>=0;i--)
		if((1<<i)<=k)
			k-=(1<<i),a=fa[a][i];
	if(a==b)return a;
	for(int i=18;i>=0;i--)
		if(fa[a][i]!=fa[b][i])
			a=fa[a][i],b=fa[b][i];
	return fa[a][0];
}
int sol(int lca,int y){
	if(dep[lca]>dep[y])
		swap(lca,y);
	int k=dep[y]-dep[lca];
	int ans=LLONG_MAX;
	for(int i=18;i>=0;i--)
		if((1<<i)<=k)
			k-=(1<<i),ans=min(ans,l[y][i]),y=fa[y][i];
	return ans;
}
bool cmp(int a,int b){return dfn[a]<dfn[b];}
void bvt(){
	sort(h+1,h+k+1,cmp);
	st[top=1]=1,ed[1].clear();
	for(int i=1;i<=k;i++){
		if(h[i]==1)continue;
		int lca=LCA(st[top],h[i]);
		if(lca!=st[top]){
			while(dfn[lca]<dfn[st[top-1]])
				ed[st[top-1]].push_back({st[top],sol(st[top-1],st[top])}),top--;
			if(dfn[lca]!=dfn[st[top-1]])
				ed[lca].clear(),
				ed[lca].push_back({st[top],sol(lca,st[top])}),
				st[top]=lca;
			else ed[st[top-1]].push_back({st[top],sol(st[top-1],st[top])}),top--;
		}
		st[++top]=h[i];
		ed[h[i]].clear();
	}
	while(top>1)
		ed[st[top-1]].push_back({st[top],sol(st[top-1],st[top])}),top--;
	return ;
}
void trdp(int u){
	dp[u]=0;
	for(auto i:ed[u]){
		trdp(i.v);
		if(vis[i.v])dp[u]+=i.w;
		else dp[u]+=min(i.w,dp[i.v]);
	}
	return ;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<n;i++)
		cin>>u>>v>>w,ed[u].push_back({v,w}),ed[v].push_back({u,w});
	dfs(1,0);
	for(int i=1;i<=18;i++)
		for(int j=1;j<=n;j++)
			fa[j][i]=fa[fa[j][i-1]][i-1],
			l[j][i]=min(l[j][i-1],l[fa[j][i-1]][i-1]);
	for(int i=1;i<=n;i++)ed[i].clear();
	cin>>q;
	while(q--){
		cin>>k;
		for(int i=1;i<=k;i++)
			cin>>h[i],vis[h[i]]=1;
		bvt();
		trdp(1);
		cout<<dp[1]<<"\n";
		for(int i=1;i<=k;i++)
			vis[h[i]]=0;
	}
	return 0;
}