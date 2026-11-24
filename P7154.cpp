#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e3+5,mod=1e9+7;
int n;
int f[2][N][2];
array<int,2>a[N*2];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i][0],a[i][1]=0;
	for(int i=1;i<=n;i++)cin>>a[i+n][0],a[i+n][1]=1;
	sort(a+1,a+n*2+1);
	f[0][0][1]=1;
	for(int op=1,i=1;op<=n*2;op++,i^=1){
		for(int j=0;j<=n;j++)f[i][j][0]=f[i][j][1]=0;
		for(int j=0;j<=n;j++)
			if(a[op][1])
				f[i][j][1]=(f[i^1][j][1]+f[i^1][j+1][1]*(j+1)%mod)%mod,
				f[i][j][0]=f[i^1][j+1][0]*(j+1)%mod;
			else{
				if(j)f[i][j][1]=f[i^1][j-1][1];
				f[i][j][0]=f[i^1][j][0]+f[i^1][j][1];
				if(j)f[i][j][0]+=f[i^1][j-1][0];
				f[i][j][0]%=mod;
			}
	}
	cout<<(f[(2*n)&1][0][0]+f[(2*n)&1][0][1])%mod;
}