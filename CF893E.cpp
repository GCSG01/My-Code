#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mod=1e9+7;
int f[21][N];
int fac[N],inv[N];
int C(int n,int m){
	if(n<m||m<0)return 0;
	return fac[n]*inv[n-m]%mod*inv[m]%mod;
}
int qpow(int x,int y,int s=1){
	for(;y;x*=x,x%=mod,y>>=1)
		if(y&1)s*=x,s%=mod;
	return s;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	fac[0]=1;
	for(int i=1;i<=N-5;i++)fac[i]=fac[i-1]*i%mod;
	inv[N-5]=qpow(fac[N-5],mod-2);
	for(int i=N-5;i>=1;i--)inv[i-1]=inv[i]*i%mod;
	f[0][1]=1;
	for(int i=0;i<=20;i++)
		for(int j=1;j<=N-5;j++)
			if(f[i][j])
				for(int k=j+j;k<=N-5;k+=j)
					f[i+1][k]=(f[i+1][k]+f[i][j])%mod;
	int q;cin>>q;
	while(q--){
		int x,y;cin>>x>>y;
		int ans=0;
		for(int i=0;i<=min(20ll,y);i++)
			ans=(ans+f[i][x]*C(y,i)%mod)%mod;
		cout<<ans*qpow(2,y-1)%mod<<"\n";
	}
}