#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,a[N],b[N],c[N];
bool check(int mid){
	for(int i=1;i<=n;i++){
	}
	return true;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i]>>b[i]>>c[i];
		int l=0,r=1e18,ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid))ans=mid,l=mid+1;
			else r=mid-1;
		}
		cout<<ans<<"\n";
	}
}