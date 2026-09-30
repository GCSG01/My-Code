#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=405,mod=1e9+7;
int n,m,c,f[N],C[N][N];
int qpow(int x,int y,int s=1){
	while(y){
		if(y&1)s=s*x%mod;
		x=x*x%mod,y=y>>1;
	}return s;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m>>c;
	for(int i=0;i<=400;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	for(int i=1;i<=c;i++){
		int st=0,k=1;
		for(int j=m;j>=1;j--,k=k*(i+1)%mod)
			if(j&1)st=(st+qpow(k-1,n)*C[m][j])%mod;
			else st=(st-qpow(k-1,n)*C[m][j]%mod+mod)%mod;
		f[i]=(qpow(qpow(i+1,m)-1,n)-st+mod)%mod;
	}
	int ans=f[c],an1=0;
	for(int i=1;i<=c;i++)
		if(i&1)an1=(an1+f[c-i]*C[c][i])%mod;
        else an1=(an1-f[c-i]*C[c][i]%mod+mod)%mod;
    cout<<(ans-an1+mod)%mod;
}