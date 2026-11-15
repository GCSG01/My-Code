#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int qpow(int x,int y,int s=1){
	for(;y;x*=x,x%=mod,y>>=1)
		if(y&1)s*=x,s%=mod;
	return s;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	int inv2=qpow(2,mod-2),inv6=qpow(6,mod-2);
	while(T--){
		int n,m;cin>>n>>m;
		int sum=qpow(m+1,n-1)%mod;
		int cnt=qpow(4,n-1)-qpow(3,n-1);cnt=(cnt%mod+mod)%mod;
		sum+=m%mod*(m-1)%mod*inv2%mod*cnt%mod,sum%=mod;

		cnt=qpow(m+1,n-1)-(qpow(3,n-1)-qpow(2,n-1))%mod*(m-1)%mod-qpow(2,n-1),cnt=(cnt%mod+mod)%mod;
		sum+=m*cnt%mod,sum%=mod;

		cnt=qpow(4,n-1)-qpow(3,n)+3*qpow(2,n-1)-1;cnt=(cnt%mod+mod)%mod;
		sum+=m*(m-1)%mod*(m-2)%mod*inv6%mod*cnt%mod,sum%=mod;

		cout<<(sum*qpow(2,m))%mod<<"\n";
	}
}