#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int n,a[N];
priority_queue<int,vector<int>,greater<int>>q;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	int ans=0;
	for(int i=1;i<=n;i++){
		if(!q.empty()&&q.top()<a[i])ans+=a[i]-q.top(),q.pop(),q.push(a[i]);
		q.push(a[i]);
	}cout<<ans;
}