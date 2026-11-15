#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int a[N],b[N];
void solve(){
	int n;cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
	sort(b+1,b+n+1);
	int nn=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)
		cout<<lower_bound(b+1,b+nn+1,a[i])-b<<" ";
	cout<<"\n";
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	while(T--)solve();
}