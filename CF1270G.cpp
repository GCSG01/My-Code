#include<bits/stdc++.h>
// #define int long long
using namespace std;
const int N=2e6+5;
int n,a[N];
int deg[N],vis[N];
int to[N];
vector<int>ans;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	while(T--){
		cin>>n,ans.clear();
		for(int i=1;i<=n;i++)cin>>a[i],a[i]-=i;
		for(int i=1;i<=n;i++)to[i]=-a[i],vis[i]=0;
		int x=1;
		while(!vis[x])vis[x]=1,x=to[x];
		ans.push_back(x),x=to[x];
		while(x!=ans[0])ans.push_back(x),x=to[x];
		cout<<ans.size()<<"\n";
		for(int i:ans)cout<<i<<" ";
		cout<<"\n";
	}
}