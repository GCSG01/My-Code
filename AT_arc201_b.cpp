#include<bits/stdc++.h>
#define int long long
#define i128 __int128
using namespace std;
const int N=5e5+5;
priority_queue<int>q[65];
int solve(int W,int x){
	if(!W)return 0;
	int ans=0;q[x].push(0);
	if(W&1)
		ans+=q[x].top(),q[x].pop(),W--;
	if(q[x].size()&1)
		q[x].push(0);
	int tmp=0;
	while(!q[x].empty()){
		if(tmp)
			q[x+1].push(tmp+q[x].top()),tmp=0;
		else tmp=q[x].top();
		q[x].pop();
	}
	return ans+solve(W/2,x+1);
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	while(T--){
		for(int i=0;i<=61;i++)
			while(!q[i].empty())q[i].pop();
		int n,w;cin>>n>>w;
		for(int i=1,x,y;i<=n;i++)
			cin>>x>>y,q[x].push(y);
		cout<<solve(w,0)<<"\n";
	}
}