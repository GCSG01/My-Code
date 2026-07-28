#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,mod=998244353;
int n,k;
int x[N],y[N];
int qpow(int x,int y){
    int s=1;
    while(y){
        if(y&1)s=s*x%mod;
        x*=x,x%=mod,y>>=1;
    }
    return s;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>x[i]>>y[i];
    int ans=0,s=0;
    for(int i=1;i<=n;i++){
        s=y[i];
        for(int j=1;j<=n;j++)
            if(i!=j)
                s=(k-x[j]+mod)%mod*s%mod*qpow((x[i]-x[j]+mod)%mod,mod-2)%mod;
        ans=(ans+s)%mod;
    }
    cout<<ans;
    return 0;
}