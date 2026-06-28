#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int _cnt,_head[N],_nxt[N],_to[N],_e[N];
int n,m,cnt,head[N],nxt[N],to[N],a[N],vis[N],st[N];
int tot,dfn[N],dep[N],mn[N],dp[N],fa[N][20];
void _add(int x,int y,int w){
	_nxt[++_cnt]=_head[x],_head[x]=_cnt,_to[_cnt]=y,_e[_cnt]=w;
	return ;
}
void add(int x,int y){
	nxt[++cnt]=head[x],head[x]=cnt,to[cnt]=y;
	return ;
}
void dfs(int x){
	dfn[x]=++tot,dep[x]=dep[fa[x][0]]+1;
	for(int i=_head[x];i;i=_nxt[i]){
		if(_to[i]==fa[x][0]) continue;
		fa[_to[i]][0]=x,mn[_to[i]]=min(mn[x],_e[i]);
		dfs(_to[i]);
	}
	return ;
}
int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	int k=dep[x]-dep[y];
	for(int i=18;i>=0;i--) if((1<<i)<=k) k-=(1<<i),x=fa[x][i];
	if(x==y) return x;
	for(int i=18;i>=0;i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
bool cmp(int x,int y){
	return dfn[x]<dfn[y];
}
void build(){
	sort(a+1,a+m+1,cmp);
	int top=0;
	st[++top]=1;
	for(int i=1;i<=m;i++){
		int lca=LCA(st[top],a[i]);
		if(lca!=st[top]){
			while(dfn[lca]<dfn[st[top-1]]) add(st[top-1],st[top]),--top;
			if(dfn[lca]>dfn[st[top-1]]) add(lca,st[top]),st[top]=lca;
			else add(lca,st[top]),top--;
		}
		st[++top]=a[i];
	}
	while(top>1) add(st[top-1],st[top]),top--;
	return ;
}
void DP(int x){
	dp[x]=0;
	for(int i=head[x];i;i=nxt[i]){
		DP(to[i]);
		if(vis[to[i]]) dp[x]+=mn[to[i]];
		else dp[x]+=min(mn[to[i]],dp[to[i]]);
	}
	return ;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int q;
	cin >>n;
	for(int i=1,x,y,z;i<n;i++){
		cin >>x>>y>>z;
		_add(x,y,z),_add(y,x,z);
	}
	mn[1]=LLONG_MAX,dfs(1);
	for(int i=1;i<=18;i++) for(int j=1;j<=n;j++) fa[j][i]=fa[fa[j][i-1]][i-1];
	cin >>q;
	while(q--){
		cin >>m;
		for(int i=1;i<=m;i++) cin >>a[i],vis[a[i]]=1;
		build(),DP(1);
		cout <<dp[1]<<endl,cnt=0,head[1]=0;
		for(int i=1;i<=m;i++) vis[a[i]]=0,head[a[i]]=0;
	}
	return 0;
}
