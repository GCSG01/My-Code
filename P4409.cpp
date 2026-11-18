#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,a[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	int ans=0;
	for(int i=1;i<n;i++)ans=max(ans,a[i]+a[i+1]);
	ans=max(ans,a[n]+a[1]);
	int res=0;
	for(int i=1;i<=n;i++)res+=a[i];
	res=ceil(res*1.0/(n/2));
	cout<<max(ans,res);
}