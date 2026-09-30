#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5,mod=998244353;
int inv[N],fac[N];
int pre[N],suf[N];
int y[N];
int n,m,V;
int qpow(int x,int y,int s=1){
    while(y){
        if(y&1)s*=x,s%=mod;
        x*=x,x%=mod,y>>=1;
    }return s;
}
int C(int n,int m){
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int getf(int k){
    int ans=0;
    for(int i=1;i<=n;i++){
        int cnt=qpow(V,n-i)*qpow(k,i)%mod-qpow(V-k+1,n-i);
        cnt=qpow(cnt,m)-qpow(qpow(V,n-i)*qpow(k,i)%mod,m);
        cnt=cnt*C(n,i)%mod;
        if(i&1)ans-=cnt;
        else ans+=cnt;
        ans%=mod;
    }
    if(ans<0)return ans+mod;
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>V;
    fac[0]=1;
    for(int i=1;i<=N-5;i++)fac[i]=fac[i-1]*i%mod;
    inv[N-5]=qpow(fac[N-5],mod-2);
    for(int i=N-6;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    int ans=0,d=n*m+1;
    for(int k=1;k<=min(V,d);k++)
        (ans+=getf(k))%=mod,y[k]=ans;
    if(V<=d)return cout<<ans,0;
    pre[0]=suf[d+1]=1,ans=0;
    for(int i=1;i<=d;i++)pre[i]=pre[i-1]*(V-i)%mod;
    for(int i=d;i>=1;i--)suf[i]=suf[i+1]*(V-i)%mod;
    for(int i=1;i<=d;i++){
        int cnt=y[i]*pre[i-1]%mod*suf[i+1]%mod;
        cnt=cnt*inv[i-1]%mod*inv[d-i]%mod;
        if((d-i)&1)ans-=cnt;
        else ans+=cnt;
        ans%=mod;
    }
    if(ans<0)ans+=mod;
    cout<<ans;
}