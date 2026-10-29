#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,q;
vector<int>g[N];
int ans;
int l[N],r[N];
int d[N];
void dfs(int x,int fa){
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>q;
	for(int i=1,u,v;i<n;i++)cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	for(int i=1;i<=n;i++)cin>>l[i]>>r[i];
	dfs(1,0);
	cout<<(ans?1:0);
	while(q--){
		int x,ll,rr;cin>>x>>ll>>rr;;
		if(l[x]<=d[x]&&d[x]<=r[x])ans--;
		if(ll<=d[x]&&d[x]<=rr)ans++;
		cout<<(ans?1:0);
	}
}