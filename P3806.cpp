#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e6+5;
struct node{
	int v,w;
};
vector<node>a[N];
int k[N],siz[N],maxx[N];
int vis[N],ans[N],t[N*4];
int n,m,root;
void dfs(int x,int ffa,int nsize){
	siz[x]=1,maxx[x]=0;
	for(auto y:a[x])
		if(!vis[y.v]&&y.v!=ffa)
		    dfs(y.v,x,nsize),siz[x]+=siz[y.v],maxx[x]=max(maxx[x],siz[y.v]);
	maxx[x]=max(maxx[x],nsize-siz[x]);
	if(maxx[x]<maxx[root])root=x;
	return ;
}
int tot=0,tmp[N];
int num[N],dis[N];
void find(int x,int ffa){
	num[++tot]=dis[x];
	for(auto y:a[x])
		if(y.v!=ffa&&!vis[y.v])
            dis[y.v]=dis[x]+y.w,find(y.v,x);
	return ;
}
void work(int x){
	int tmptot=0;
	for(auto y:a[x]){
		if(vis[y.v])continue;
		tot=0,dis[y.v]=y.w,find(y.v,x);
		for(int i=1;i<=tot;i++)
			for(int j=1;j<=m;j++)
				if(k[j]>=num[i])
					ans[j]|=t[k[j]-num[i]];
		for(int j=1;j<=tot;j++)
			t[num[j]]=1,tmp[++tmptot]=num[j];
	}
	for(int i=1;i<=tmptot;i++)t[tmp[i]]=0;
	t[0]=0;
	return ;
}
void solve(int x){
	vis[x]=1,t[0]=1,work(x);
	for(auto y:a[x])
		if(!vis[y.v])
            maxx[root=0]=siz[y.v],
            dfs(y.v,x,siz[y.v]),
            solve(root);
	return ;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1,u,v,w;i<n;i++)
		cin>>u>>v>>w,
        a[u].push_back({v,w}),
		a[v].push_back({u,w});
	for(int i=1;i<=m;i++)cin>>k[i];
	maxx[0]=n;
	dfs(1,0,n);
	solve(root);
	for(int i=1;i<=m;i++)
        cout<<(ans[i]?"AYE\n":"NAY\n");
	return 0;
}