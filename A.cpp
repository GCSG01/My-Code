#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=5e3+5,mod=1e9+7;
int n,f[N][N],g[N][N];
string s;
int ans[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	freopen("mountain.in","r",stdin);
	freopen("mountain.out","w",stdout);
	int cid;cin>>cid>>s,n=s.size(),s=" "+s;
	f[0][0]=g[n+1][0]=1;
	for(int i=0;i<n;i++)
		for(int j=0;j<=i;j++){
			(f[i+1][j]+=f[i][j]*j%mod)%=mod;
			if(s[i+1]=='U')
				(f[i+1][j+1]+=f[i][j]*(j+1)%mod)%=mod;
			else if(j)
				(f[i+1][j-1]+=f[i][j]*(j-1)%mod)%=mod;
		}
	if(n==1)return cout<<1,0;
	for(int i=n+1;i>1;i--)
		for(int j=0;j<=n-i+1;j++){
			(g[i-1][j]+=g[i][j]*j%mod)%=mod;
			if(s[i-1]=='D')
				(g[i-1][j+1]+=g[i][j]*(j+1)%mod)%=mod;
			else if(j)
				(g[i-1][j-1]+=g[i][j]*(j-1)%mod)%=mod;
		}
	for(int i=1;i<=n;i++){
		if(i==1)
			ans[i]=g[2][1];
		else if(i==n)
			ans[i]=f[n-1][1];
		else
			for(int j=1;j<=n;j++){
				int L=f[i-1][j],R=g[i+1][j-1];
				(ans[i]+=L*R%mod)%=mod;
				R=g[i+1][j];
				(ans[i]+=L*R%mod*2%mod)%=mod;
				R=g[i+1][j+1];
				(ans[i]+=L*R%mod)%=mod;
			}
	}
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<" ";
}