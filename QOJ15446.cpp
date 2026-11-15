#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5,mod=1e9+7;
int n,m=2,fib[N];
int fac[N],vis[30][N];
int qpow(int x,int y,int s=1){
	while(y){
		if(y&1)s*=x,s%=mod;
		x*=x,x%=mod,y>>=1;
	}return s;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n,fib[1]=1;
	for(int i=2;;i++){
		fib[i]=fib[i-1]+fib[i-2];
		if(fib[i]>n){
			m=i;break;
		}
	}
	int pw=n,ans=0;
	for(int i=1;i<=n;i++,pw=pw*n%mod)ans+=pw,ans%=mod;
	fac[0]=1;
	for(int i=1;i<=m;i++)fac[i]=fac[i-1]*i%mod;
	vis[0][0]=1;
	int inv2=qpow(2,mod-2);
	for(int i=1;i<=min(n,m);i++){
		for(int j=0;j<=n;j++){
			vis[i][j]=vis[i-1][j];
			if(j>=fib[i])vis[i][j]=(vis[i][j]+vis[i][j-fib[i]])%mod;
			if(j+fib[i]+fib[i-1]<=n)
				ans-=fac[i]*vis[i][j]%mod,ans%=mod;
			else if(j+fib[i]<=n)
				ans-=fac[i]*vis[i][j]%mod*inv2%mod,ans%=mod;			
		}
	}
	if(ans<0)ans+=mod;
	cout<<ans;
}