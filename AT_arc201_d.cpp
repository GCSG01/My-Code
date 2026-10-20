#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int n,m,a[N],b[N];
bool check(int mid){
	for(int i=1;i<=n;i++)
		if(b[i+mid]<a[i])return false;
	return true;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++)cin>>a[i],a[i]=(m-a[i])%m;
		for(int i=1;i<=n;i++)cin>>b[i];
		sort(a+1,a+n+1),sort(b+1,b+n+1);
		for(int i=1;i<=n;i++)b[n+i]=b[i]+m;
		int l=-1,r=n+1,ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid))r=mid-1,ans=mid;
			else l=mid+1;
		}
		int Ans=0;
		for(int i=1;i<=n;i++)
			Ans=max(Ans,b[i+ans]-a[i]);
		cout<<Ans<<"\n";
	}
}