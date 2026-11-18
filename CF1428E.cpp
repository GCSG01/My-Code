#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,k,a[N];
priority_queue<array<int,3>>q;
int f(int x,int k){
	int b=x/k;
	return (b+1)*(b+1)*(x%k)+b*b*(k-x%k);
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	int ans=0;
	for(int i=1;i<=n;i++)
		ans+=f(a[i],1),q.push({f(a[i],1)-f(a[i],2),i,2});
	k-=n;
	while(k--){
		auto [c,i,kk]=q.top();q.pop();
		ans-=c;
		if(kk<a[i])
			q.push({f(a[i],kk)-f(a[i],kk+1),i,kk+1});
	}
	cout<<ans;
}