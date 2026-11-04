#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,q,l[N],r[N];
int fa[N],ord[N];
int Mx[N],dp[N];
vector<int>g[N];
void dfs(){
	int tot=1;
	fa[1]=-1,ord[0]=1;
	for(int i=0;i<tot;i++){
		int x=ord[i];
		for(int y:g[x])
			if(y!=fa[x])fa[y]=x,ord[tot++]=y;
	}
}
void update(int x){
	int mx=l[x],sum=0;
	for(int y:g[x])
		if(y!=fa[x])mx=max(mx,Mx[y]),sum+=dp[y];
	Mx[x]=mx,dp[x]=min(r[x],1+sum);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>q;
	for(int i=1,u,v;i<n;i++)cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	for(int i=1;i<=n;i++)cin>>l[i]>>r[i];
	dfs();
	for(int i=n-1;i>=0;i--)update(ord[i]);
	int ans=0;
	for(int i=1;i<=n;i++)
		if(Mx[i]>dp[i])ans++;
	cout<<(ans==0);
	while(q--){
		int x,nl,nr;cin>>x>>nl>>nr,l[x]=nl,r[x]=nr;
		for(int z=x;z!=-1;z=fa[z]){
			if(Mx[z]>dp[z])ans--;
			update(z);
			if(Mx[z]>dp[z])ans++;
		}
		cout<<(ans==0);
	}
}