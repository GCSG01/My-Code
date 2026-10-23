#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,m,a[N];
int ans=0;
bool check(int mid){
	int mx=0;
	for(int i=1;i<=mid;i++)
		mx=max(mx,a[i]+a[mid*2-i+1]);
	for(int i=1;i<=n-mid;i++){
		int cnt=a[2*mid+i]+a[2*n-i+1]-m;
		if(cnt<0)return false;
		mx=max(mx,cnt);
	}
	return ans=min(ans,mx),true;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m,ans=m;
	for(int i=1;i<=n*2;i++)cin>>a[i];
	sort(a+1,a+n*2+1);
	int l=0,r=n*2;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))r=mid-1;
		else l=mid+1;
	}
	cout<<ans;
}