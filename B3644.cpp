#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
queue<int>q;
int ans[N],in[N]; 
vector<int>g[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,cnt=0;cin>>n;
	for(int i=1;i<=n;i++)
		while(1){
			int x;cin>>x;
			if(!x)break;
			g[i].push_back(x),in[x]++;
		}
	for(int i=1;i<=n;i++)
		if(!in[i])q.push(i);
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int y:g[x])
			if(!--in[y])q.push(y);
		ans[++cnt]=x;
	}
	for(int i=1;i<=cnt;i++)cout<<ans[i]<<" ";
}