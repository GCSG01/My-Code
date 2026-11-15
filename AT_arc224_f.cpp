#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,mod=998244353;
int n,k,a[N];
int fac[N],inv[N];
int qpow(int x,int y,int s=1){
	for(;y;x*=x,x%=mod,y>>=1)
		if(y&1)s*=x,s%=mod;
	return s;
}
void init(){
	fac[0]=1;
	for(int i=1;i<=N-5;i++)fac[i]=fac[i-1]*i%mod;
	inv[N-5]=qpow(fac[N-5],mod-2);
	for(int i=N-5;i>=1;i--)inv[i-1]=inv[i]*i%mod;
}
int C(int n,int m){
	if(n<m||m<0)return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int Sum=0,pos,inv2=499122177;
void subk(){
	k--,Sum-=C(pos-1,k),Sum=(Sum%mod+mod)%mod;
}
void subpos(){
	Sum=(Sum+C(pos-2,k-1))*inv2%mod,Sum=(Sum%mod+mod)%mod,pos--;
}
int calc(){
	return Sum;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T,init();
	while(T--){
		cin>>n>>k,Sum=0;
		for(int i=1;i<=n;i++)cin>>a[i];
		int ans=0,mx=0;
		for(int i=0;i<k;i++)
			Sum+=C(n-1,i),Sum=(Sum%mod+mod)%mod;
		for(int i=n;i>=n-k+1;i--)mx|=a[i];
		if(!mx)ans++;
		for(pos=n;pos>=1;){
			if((a[pos]&mx)==mx)
				ans+=calc(),ans%=mod;
			else mx=mx^(mx&a[pos]),subk();
			subpos();
		}
		cout<<ans<<"\n";
	}
}