#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=305,M=1e5+5,mod=1e9+7;
int n,m,t,a[N][N];
int qpow(int x,int y,int s=1){
    while(y){
        if(y&1)s*=x,s%=mod;
        x*=x,x%=mod,y>>=1;
    }
    return s;
}
int det(){
	int ans=1;
	for(int i=2;i<n;i++){
		for(int j=i+1;j<=n;j++)
            if(a[j][i]&&!a[i][i])
                swap(a[i],a[j]),ans*=-1;
		int inv=qpow(a[i][i],mod-2);
		for(int j=i+1;j<=n;j++){
			int d=inv*a[j][i]%mod;
			for(int k=i;k<=n;k++)
                (a[j][k]+=-d*a[i][k]%mod)%=mod;
		}
	}
	for(int i=2;i<=n;i++)
        (ans*=a[i][i])%=mod;
	return (ans+mod)%mod; 
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>t;
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w;
        (a[u][v]+=(mod-w))%=mod,(a[v][v]+=w)%=mod;
		if(!t)(a[v][u]+=mod-w)%=mod,(a[u][u]+=w)%=mod;
    }
    cout<<det();
}