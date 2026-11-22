#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+5,mod=998244353;
int n;
int f[N][N];
int siz[N];
int fac[N],inv[N],faci[N];
int tmp[N],val[N];
vector<int>g[N];
int C(int n,int m){
	if(n<0||n<m)return 0;
	return fac[n]*faci[n-m]%mod*faci[m]%mod;
}
int qpow(int x,int y,int s=1){
	for(;y;x*=x,x%=mod,y>>=1)
		if(y&1)s*=x,s%=mod;
	return s;
}
void dfs1(int x){
	siz[x]=1,val[x]=1;
	for(int y:g[x])
		dfs1(y),siz[x]+=siz[y],val[x]=val[x]*val[y]%mod;
	val[x]=val[x]*inv[siz[x]]%mod;
}
void dfs2(int x){
	for(int y:g[x]){
		int cnt=val[x]*qpow(val[y],mod-2)%mod;
		for(int i=1;i<=n;i++)
			tmp[i]=f[x][i]*C(n-siz[y]-i,siz[x]-siz[y]-1)%mod*fac[siz[x]-siz[y]-1]%mod*cnt%mod*siz[x]%mod;
		for(int i=1;i<=n;i++)
			tmp[i]+=tmp[i-1],tmp[i]%=mod;
		for(int i=1;i<=n;i++)
			f[y][i]=tmp[i-1];
		dfs2(y);
	}
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	fac[0]=faci[0]=fac[1]=faci[1]=inv[1]=1;
	for(int i=2;i<=N-5;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=2;i<=N-5;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int i=2;i<=N-5;i++)faci[i]=faci[i-1]*inv[i]%mod;
	cin>>n;
	for(int i=2,fa;i<=n;i++)cin>>fa,g[fa].push_back(i);
	dfs1(1),f[1][1]=1,dfs2(1);
	for(int i=1;i<=n;i++)
		cout<<f[i][i]*C(n-i,siz[i]-1)%mod*fac[siz[i]]%mod*val[i]%mod<<" ";
}