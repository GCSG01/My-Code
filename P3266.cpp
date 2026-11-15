#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e6+5,mod=1e9+7;
int n,m;
int inv[N],fac[N];
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
inline void flip1(int &x,int &y){
	swap(x,y),x--,y++;
}
inline void flip2(int &x,int &y){
	swap(x,y),x+=m+2,y-=m+2;
}
int calc(int n,int m){
	if(n<0||m<0)return 0;
	return fac[n+m]*inv[n]%mod*inv[m]%mod;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m,init();
	int x=n+m+1,y=n,ans=calc(x,y);
	while(x>=0&&y>=0)
		flip1(x,y),ans-=calc(x,y),flip2(x,y),ans+=calc(x,y),ans%=mod;
	x=n+m+1,y=n;
	while(x>=0&&y>=0)
		flip2(x,y),ans-=calc(x,y),flip1(x,y),ans+=calc(x,y),ans%=mod;
	if(ans<0)ans+=mod;
	cout<<ans;
}