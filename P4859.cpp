#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+5,mod=1e9+9;
int n,k,a[N],b[N];
int pre[N];
int f[N][N];
int fac[N],inv[N];
int qpow(int x,int y,int s=1){
    while(y){
        if(y&1)s*=x,s%=mod;
        x*=x,x%=mod,y>>=1;
    }return s;
}
int C(int n,int m){
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)cin>>b[i];sort(b+1,b+n+1);
    if((n+k)&1)return cout<<0,0;
    int m=(n+k)/2;
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=qpow(fac[n],mod-2);
    for(int i=n-1;i>=1;i--)inv[i]=inv[i+1]*(i+1)%mod;
    int tot=0;
    for(int i=1;i<=n;i++){
        while(b[tot+1]<a[i]&&tot<n)tot++;
        pre[i]=tot;
    }
    f[0][0]=1;
    for(int i=1;i<=n;i++)
        for(int j=0;j<=i;j++){
            f[i][j]=f[i-1][j];
            if(j>0&&pre[i]-j+1>0)f[i][j]+=f[i-1][j-1]*(pre[i]-j+1)%mod;
            f[i][j]%=mod;
        }
    int ans=0;
    for(int i=m;i<=n;i++){
        int cnt=C(i,m)*f[n][i]%mod*fac[n-i]%mod;
        if((i-m)%2)ans-=cnt;
        else ans+=cnt;
        ans%=mod;
    }
    if(ans<0)ans+=mod;
    cout<<ans;
}