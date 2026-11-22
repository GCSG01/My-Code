#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e2+5,mod=998244353;
int n,m,f[N][N],C[N][N];
vector<pair<int,int>>v[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	C[0][0]=1;
	for(int i=1;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	for(int i=1,l,r,x;i<=m;i++)
		cin>>l>>r>>x,v[l].push_back({r,x});
	for(int i=0;i<=n;i++)f[i+1][i]=1;
	for(int r=1;r<=n;r++){
		vector<int>st(r+1,1);
		for(auto[x,y]:v[r])
			if(x<=r)st[y]=0;
		f[r][r]=st[r];
		for(int l=r-1;l>=1;l--){
			for(auto[x,y]:v[l])
				if(x<=r)st[y]=0;
			for(int k=l;k<=r;k++)
				f[l][r]+=f[l][k-1]*f[k+1][r]%mod*C[r-l][k-l]%mod*st[k]%mod,f[l][r]%=mod;
		}
	}
	cout<<f[1][n];
}