#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1.5e2+5,mod=998244353;
int n,a[N];
int f[2][N*N][N][2];
int fac[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n,fac[0]=1;
	int sum=0;
	for(int i=1;i<=n;i++)cin>>a[i],fac[i]=fac[i-1]*i%mod,sum+=a[i];
	if(sum&1)return cout<<0,0;
	f[0][0][0][0]=1;
	for(int op=1,i=1;op<=n;op++,i^=1){
		memset(f[i],0,sizeof f[i]);
		for(int j=0;j<=10000;j++)
			for(int k=0;k<=op;k++){
				f[i][j][k][0]=(f[i^1][j][k][0]+f[i^1][j][k][1])%mod;
				if(j>=a[op]&&k>=1)
					f[i][j][k][1]=(f[i^1][j-a[op]][k-1][0]+f[i^1][j-a[op]][k-1][1])%mod;
			}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		ans+=(f[n&1][sum/2][i][0]+f[n&1][sum/2][i][1])%mod*fac[i]%mod*fac[n-i]%mod,ans%=mod;
	cout<<ans;
}