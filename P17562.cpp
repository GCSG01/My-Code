#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mod=998244353;
int n,g[N];
int fac[N],inv[N];
int qpow(int x,int y,int s=1){
    while(y){
        if(y&1)s*=x,s%=mod;
        x*=x,x%=mod,y>>=1;
    }return s;
}
int C(int n,int m){
    if(n<0||m<0)return 0;
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=0;i<=n+1;i++)cin>>g[i];
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=qpow(fac[n],mod-2);
    for(int i=n;i;i--)inv[i-1]=inv[i]*i%mod;
    int ans=0,pos=n+1,cnt=0;
    g[n+1]-=g[0],g[0]=-1;
    for(int i=1;i<=n;i++){
        if(g[i]==g[i-1])cnt++;
        else cnt=1;
        if(i==n||g[i]!=g[i+1])cnt=0;
        ans+=C(n-1-cnt,i-1-cnt),ans%=mod;
    }
    cout<<2*n*g[n+1]<<" "<<ans*ans%mod;
}