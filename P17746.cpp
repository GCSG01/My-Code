#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int n,k;
int a[N];
struct node{
	int l,r,cnt;
};
bool operator<(node A,node B){
	return A.l>B.l;
}
vector<node>ls[N];
priority_queue<node>q;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1,x;i<=n;i++)cin>>x,a[i]=x-a[i];
	for(int i=1;i<=n;i++)
		if(a[i]<0)return cout<<-1,0;
	int cnt=0;
	for(int i=1;i<=n;i++){
		while(!q.empty()&&i-q.top().l+1>k){
			auto now=q.top();q.pop();
			ls[i-1].push_back({now.l,i-1,now.cnt}),cnt-=now.cnt;
		}
		if(cnt<a[i])
			q.push({i,-1,a[i]-cnt}),cnt=a[i];
		else{
			while(!q.empty()&&cnt>a[i]){
				auto now=q.top();q.pop();
				if(cnt-now.cnt>=a[i])cnt-=now.cnt,now.r=i-1,ls[i-1].push_back(now);
				else ls[i-1].push_back({now.l,i-1,cnt-a[i]}),now.cnt-=cnt-a[i],cnt=a[i],q.push(now);
			}
		}
	}
	while(!q.empty()){
		auto now=q.top();q.pop(),cnt-=now.cnt;
		ls[n].push_back({now.l,n,now.cnt});
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		for(auto j:ls[i])
			ans+=j.cnt;
	cout<<ans;
}