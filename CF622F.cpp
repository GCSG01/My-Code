#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mod=1e9+7;
int a[N];
int pre[N],suf[N];
int jc[N],inv[N];
int qpow(int x,int y){
    int s=1;
    while(y){
        if(y&1)s*=x,s%=mod;
        x*=x,x%=mod,y>>=1;
    }
    return s;
}
int get(int n,int k){
    int ans=0,y=0;
    jc[0]=1;
    for(int i=1;i<=k+2;i++)jc[i]=jc[i-1]*i%mod;
    pre[0]=1,suf[k+3]=1;
    for(int i=1;i<=k+2;i++)pre[i]=pre[i-1]*(n-i)%mod;
    for(int i=k+2;i>=1;i--)suf[i]=suf[i+1]*(n-i)%mod;
    for(int i=1;i<=k+2;i++){
        y=(y+qpow(i,k))%mod;
        int sum=pre[i-1]*suf[i+1]%mod*y%mod;
        ans+=sum*qpow(jc[i-1]*((k-i)&1?-1:1)*jc[k+2-i]%mod,mod-2)%mod,ans%=mod;
    }
    if(ans<0)ans+=mod;
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n,k;cin>>n>>k;
    cout<<get(n,k)<<"\n";
}