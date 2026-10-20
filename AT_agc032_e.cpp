#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,m,a[N];
bool check(int mid){
	for(int i=1;i<=mid;i++){
	}
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n*2;i++)cin>>a[i];
	sort(a+1,a+n*2+1);
	int l=0,r=n*2,ans=0;
	for(int i=n;i>=1;i--)
		if(a[i]+a[n]<m){
			l=i;break;
		}
	while(l<=r){
		int mid=(l+r)>>1,cnt=check(mid);
		if(cnt<ans)r=mid-1,ans=cnt;
		else l=mid+1;
	}
	cout<<ans;
}