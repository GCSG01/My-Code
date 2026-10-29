#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+5,mod=998244353;
int qpow(int x,int y,int s=1){
	for(;y;x*=x,x%=mod,y>>=1)
		if(y&1)s*=x,s%=mod;
	return s;
}
int f[N];
int fac[N],inv[N];
int C(int n,int m){
	if(n<m)return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	fac[0]=1;
	for(int i=1;i<=N-5;i++)fac[i]=fac[i-1]*i%mod;
	inv[N-5]=qpow(fac[N-5],mod-2);
	for(int i=N-5;i>=1;i--)inv[i-1]=inv[i]*i%mod;
	int n,op;cin>>n>>op;
	if(!op){
		f[1]=1,f[2]=3;
		for(int i=3;i<=n;i++)
			f[i]=3*f[i-1]%mod-f[i-2],f[i]=(f[i]%mod+mod)%mod;
		int ans=0;
		for(int i=1;i<=n;i++)ans^=f[i]*i;
		return cout<<ans,0;
	}
	// dp[0][0]=1;
	// for(int i=1;i<=50;i++)
	// 	for(int k=i;k<=n;k++)
	// 		for(int j=1;j<=k-i+1;j++)
	// 			dp[i][k]+=dp[i-1][k-j]*j%mod,dp[i][k]%=mod;
	int ans=0;
	for(int k=1;k<=n;k++){
		int sum=0;
		for(int i=1;i<=50;i++)
			sum+=C(k+i-1,2*i-1),sum%=mod;
		ans^=sum*k;
	}
	cout<<ans;
}