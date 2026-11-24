#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e4+5;
int n,k,m;
array<int,2>a[N];
priority_queue<int,vector<int>,greater<int>>q;
priority_queue<array<int,2>,vector<array<int,2>>,greater<array<int,2>>>q1,q2;
int vis[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>k>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i][0]>>a[i][1],q1.push({a[i][0],i}),q2.push({a[i][1],i});
	for(int i=1;i<=k;i++)q.push(0);
	int ans=0;
	while(!q1.empty()&&m>=0){
		auto x=q1.top(),y=q2.top();
		if(vis[x[1]]){
			q1.pop();continue;
		}
		if(vis[y[1]]){
			q2.pop();continue;
		}
		if(q.top()>x[0]-y[0])
			m-=x[0],q1.pop(),vis[x[1]]=1;
		else{
			m-=y[0]+q.top(),q.pop(),q2.pop();
			vis[y[1]]=1,q.push(a[y[1]][0]-a[y[1]][1]);
		}
		if(m>=0)ans++;
	}
	cout<<ans;
}