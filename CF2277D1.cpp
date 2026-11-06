#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int dfs(int n){
	if(n<=1)return n;
	if(n==2)return 3;
	if(n==3)return 2;
	int k=__lg(n);
	return min(k+(1ll<<(k+1))-n,k+1+dfs(n-(1ll<<k)+2));
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	while(T--){
		int l,r,ans=0;cin>>l>>r;
		for(int i=l;i<=r;i++)
			ans=(ans+dfs(i))%mod;
		cout<<ans<<"\n";
	}
}