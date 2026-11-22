#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,mx;
vector<int>g[N];
int fa[N];
bitset<N>vis;
vector<int>ans;
void dfs(int x,int ffa,int d,int &pos){
	fa[x]=ffa;
	if(d>mx)
		mx=d,pos=x;
	for(int y:g[x])
		if(y!=ffa)
			dfs(y,x,d+1,pos);
}
void solve(int x,int d,int rt,int &mxd,bool flag){
	if(d>2)
		cout<<"NO",exit(0);
	mxd=max(mxd,d);
	if(flag&&d==mxd-1)
		ans.push_back(x),ans.push_back(rt);
	for(int y:g[x])
		if(!vis[y])
			vis[y]=1,solve(y,d+1,rt,mxd,flag);
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int m;cin>>n>>m;
	for(int i=1,u,v;i<=m;i++)
		cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	if(n-1!=m)return cout<<"NO\n",0;
	if(n==1)return cout<<"YES\n1\n1\n",0;
	if(n==2)return cout<<"YES\n2\n1 1\n",0;
	int a=1,b=1;
	mx=-1,dfs(1,0,0,a);
	mx=-1,dfs(a,0,0,b);
	vector<int>e;
	for(int x=b;x;x=fa[x])
		e.push_back(x),vis[x]=1;
	for(int i:e){
		if(i==b||i==a)continue;
		ans.push_back(i);
		for(int j:g[i])
			if(!vis[j]){
				int mxd=0;
				vis[j]=1,solve(j,1,i,mxd,0),solve(j,1,i,mxd,1);
			}
	}
	cout<<"YES\n";
	cout<<ans.size()*2<<"\n";
	for(int i:ans)cout<<i<<" ";
	reverse(ans.begin(),ans.end());
	for(int i:ans)cout<<i<<" ";
}