#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1.5e2+5,mod=12345678;
int n,m,k;
int f[N][N][22][22];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m>>k;
	f[0][0][0][0]=1;
	for(int i=0;i<=n;i++)
		for(int j=0;j<=m;j++)
			for(int a=0;a<=min(k,i);a++)
				for(int b=0;b<=min(k,j);b++)
					(f[i+1][j][a+1][max(0ll,b-1)]+=f[i][j][a][b])%=mod,
					(f[i][j+1][max(0ll,a-1)][b+1]+=f[i][j][a][b])%=mod;
	int ans=0;
	for(int i=0;i<=k;i++)
		for(int j=0;j<=k;j++)
			ans+=f[n][m][i][j],ans%=mod;
	cout<<ans;
}