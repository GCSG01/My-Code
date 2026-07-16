#include<bits/stdc++.h>
using namespace std;
const int N=4e6+5;
int n,m,k;
int cnt,sum;
int a[N];
int vis[N],top;
int st[N],dfn[N],low[N];
vector<int>v[N];
int f[N];
void add(int x,int y){
	v[x].push_back(y);
}
void tarjan(int x){
	dfn[x]=low[x]=++cnt;
	st[++top]=x,f[x]=1;
	for(int i=0;i<v[x].size();i++){
		int y=v[x][i];
		if(!dfn[y])
			tarjan(y),low[x]=min(low[x],low[y]);
		else if(f[y])
			low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]){
		sum++;
		int xx;
		do{
			xx=st[top--],vis[xx]=sum,f[xx]=0;
		}while(xx!=x);
	}
	return ;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m>>k;
	for(int i=1,u,v;i<=m;i++)
		cin>>u>>v,add(u+n,v),add(v+n,u);
	for(int i=1;i<=k;i++){
		int w;cin>>w;
		for(int j=1;j<=w;j++){
			cin>>a[j];
			add(a[j]+2*n,a[j]+n);
			add(a[j]+3*n,a[j]+n);
		}
		for(int j=1;j<w;j++){
			add(a[j+1]+2*n,a[j]+2*n);
			add(a[j]+3*n,a[j+1]+3*n);
			add(a[j],a[j+1]+3*n);
			add(a[j+1],a[j]+2*n);
		}
	}
	for(int i=1;i<=2*n;i++)
		if(!dfn[i])
			tarjan(i);
	for(int i=1;i<=n;i++)
		if(vis[i]==vis[i+n])
			return cout<<"NIE",0;
	cout<<"TAK";
	return 0;
}