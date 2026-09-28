#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=205,mod=998244353;
int k,n[N],m[N],a[N][N],f[N][N];
int qpow(int x,int y,int s=1){
    while(y){
        if(y&1)s*=x,s%=mod;
        x*=x,x%=mod,y>>=1;
    }return s;
}
int det(int n){
	int ans=1;
	for(int i=1;i<=n;i++){
		if(!a[i][i]){
			for(int j=i+1;j<=n;j++)
				if(a[j][i]){
                    swap(a[i],a[j]),ans=-ans;
                    break;
                } 
		}
		if(!a[i][i])return 0;
		ans=ans*a[i][i]%mod; 
		int inv=qpow(a[i][i],mod-2);
		for(int j=i;j<=n;j++)
            a[i][j]=a[i][j]*inv%mod;
        for(int j=i+1;j<=n;j++)
            for(int k=n;k>=i;k--)
				a[j][k]-=a[i][k]*a[j][i]%mod,a[j][k]%=mod;
	}
    ans%=mod;if(ans<0)ans+=mod;
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        cin>>k;
        for(int i=1;i<=k;i++)cin>>n[i];
        for(int i=2;i<=k;i++)cin>>m[i];
        memset(a,0,sizeof a);
        for(int i=1;i<=n[1];i++)a[i][i]=1;
        for(int i=2;i<=k;i++){
            for(int j=1;j<=m[i];j++){
                int u,v;cin>>u>>v;
                for(int o=1;o<=n[1]*2;o++)
                    (f[o][v]+=a[o][u])%=mod;
            }
            for(int j=1;j<=n[1]*2;j++)
                for(int o=1;o<=n[1]*2;o++)
                    a[j][o]=f[j][o],f[j][o]=0;
        }
        cout<<det(n[1])<<"\n";
    }
}