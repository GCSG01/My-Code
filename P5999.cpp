#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+5,mod=1e9+7;
int f[N][N];
int n,s,t;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>s>>t;
	f[1][1]=1;
	for(int i=2;i<=n;i++)
		for(int j=1;j<=i;j++)
			if(i!=s&&i!=t)
				f[i][j]=f[i-1][j-1]*(j-(i>s)-(i>t))%mod+f[i-1][j+1]*j%mod,f[i][j]%=mod;
			else f[i][j]=(f[i-1][j]+f[i-1][j-1])%mod;
	cout<<f[n][1];
}