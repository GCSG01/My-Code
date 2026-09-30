#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=255,mod=1e4+7;
int n,m;
int f[N][N];
int qpow(int x,int y,int s=1){
    while(y){
        if(y&1)s*=x,s%=mod;
        x*=x,x%=mod,y>>=1;
    }
    return s;
}
int det(int n){
    int ans=1;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++)
			if(f[j][i]){
				swap(f[i],f[j]),ans*=-1;
				break;
			}
		int inv=qpow(f[i][i],mod-2);
		for(int j=i+1;j<=n;j++)
			for(int k=n;k>=i;k--)
				(f[j][k]-=f[j][i]*inv%mod*f[i][k]%mod)%=mod;
	}
	for(int i=1;i<=n;i++)
        (ans*=f[i][i])%=mod;
    if(ans<0)ans+=mod;
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1,u,v;i<=m;i++)
        cin>>u>>v,f[v][u]=-1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            f[j][j]-=(i!=j)*f[i][j];
    for(int i=1;i<n;i++)
        for(int j=1;j<n;j++)
            f[i][j]=f[i+1][j+1];
    cout<<det(n-1);
}