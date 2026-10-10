#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e4+5,mod=998244353;
int n,m,a[N];
int pow2[N];
int fac[N],inv[N];
int qpow(int x,int y,int s=1){
	for(;y;x*=x,x%=mod,y>>=1)
		if(y&1)s*=x,s%=mod;
	return s;
}
void init(){
	pow2[0]=1;
	for(int i=1;i<=N-5;i++)pow2[i]=2*pow2[i-1]%mod;
	fac[0]=inv[0]=1;
	for(int i=1;i<=N-5;i++)fac[i]=fac[i-1]*i%mod;
	inv[N-5]=qpow(fac[N-5],mod-2);
	for(int i=N-6;i>=1;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
inline int C(int n,int m){
    if(m>n)return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T>>T;
	init();
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+n+1);
		int ans=0;
		for(int i=1;i<=n;i++){
			int pos=0;
			for(int j=i+1;j<=n;j++){
				if(a[i]==a[j]||m-2-n+j<0)continue;
				if(a[j]>=a[i]*2)break;
				while(pos<n&&a[pos+1]+a[i]<a[j])pos++;
				ans=(ans+C(n-i-1,m-2-n+j)*pow2[pos])%mod;
			}
		}
		cout<<(pow2[n]-ans+mod)%mod<<"\n";
	}
}