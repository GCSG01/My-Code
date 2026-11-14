#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1e4+5;
const int mod=998244353;
string s;
int n;
int cnt[N],t[N];
int fac[N],inv[N];
int f[5][N];
int val[N];
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
int get(char c){
	if(c=='A')return 1;
	if(c=='G')return 2;
	if(c=='C')return 3;
	return 4;
}
int C(int n,int m){
	if(m==0)return 1;
	if(n<m)return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	freopen("rna.in","r",stdin);
	freopen("rna.out","w",stdout);
	cin>>s,init();
	if(s=="#")
		t[1]=t[2]=t[3]=t[4]=0;
	else{
		n=s.size(),s=" "+s;
		for(int i=1;i<=n;i++)t[get(s[i])]++;
	}
	int sum=0;
	for(int i=1;i<=4;i++)
		cin>>cnt[i],sum+=cnt[i];
	f[0][0]=1;
	for(int i=1;i<=4;i++){
		for(int j=0;j<=cnt[i];j++)
			val[j]=C(t[i]+j-1,j)*inv[cnt[i]-j]%mod;
		for(int j=sum;j>=0;j--)
			for(int k=0;k<=min(cnt[i],j);k++)
				f[i][j]+=f[i-1][j-k]*val[k]%mod,f[i][j]%=mod;
	}
	int ans=0;
	for(int i=0;i<=sum;i++)
		if(i&1)ans-=inv[n+i]*f[4][i]%mod,ans%=mod;
		else ans+=inv[n+i]*f[4][i]%mod,ans%=mod;
	ans=ans*fac[n+sum]%mod;
	if(ans<0)ans+=mod;
	cout<<ans;
}