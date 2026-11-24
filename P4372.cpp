#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,t[N];
array<int,2>a[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	int ans=0;
	for(int i=1;i<=n;i++)cin>>a[i][0],a[i][1]=i;
	sort(a+1,a+n+1);
	int mx=0;
	for(int i=1;i<=n;i++)
		mx=max(mx,a[i][1]),t[i]=max(mx-i,1ll);
	for(int i=1;i<=n;i++)ans+=max(t[i-1],t[i]);
	cout<<ans;
}