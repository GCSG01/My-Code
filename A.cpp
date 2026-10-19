#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e6+5;
int n,a[N];
vector<int>g[N];
int sum[N],cnt[N];
int ans[N];
void dfs(int x,int fa){
    int tot=2*a[x];
    for(int y:g[x])
        if(y!=fa)
            dfs(y,x),tot=max(0ll,tot-min(a[x],sum[y])),ans[x]+=ans[y];
    cnt[x]=2*a[x]-tot,
    sum[x]=min(a[x],tot),
    ans[x]+=a[x]-cnt[x];
}
int u[N],v[N];
namespace Generate{
	int n,seed;
	static const int mod=1e9;
	int Rand(int x){
		seed=(1ll*seed*0x66CCF+19260817ll)%x+1;
		seed=(1ll*seed*0x77CCF+20060428ll)%x+1;
		seed=(1ll*seed*0x88CCF+12345678ll)%x+1;
		seed=(1ll*seed*0x33CCCCFF+10086001ll)%x+1;
		return seed;
	}
	void RS(int* a, int* u, int* v){ //你需要传入三个参数，分别表示点权，一条边的两个端点 
		int cnt=0;
		for(int i=1;i<=n;i++)a[i]=Rand(mod); 
		for(int i=2;i<=n;i++){
			int fa=Rand(i-1);
			cnt++;
			u[cnt]=fa,v[cnt]=i;
		}
	}
};
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int op;cin>>op;
	if(op==1){
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=1,u,v;i<n;i++)
            cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	}else{
		int n;cin>>Generate::seed>>n;
		Generate::n=n;
		Generate::RS(a,u,v);
        for(int i=1;i<n;i++)
            g[u[i]].push_back(v[i]),g[v[i]].push_back(u[i]);
		for(int i=1;i<=n;i++)
			cout<<g[i].size();
	}
    dfs(1,0);
    // cout<<ans[1];
}