#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+5,mod=1e9+7;
int qpow(int x,int y,int s=1){
    while(y){
        if(y&1)s*=x,s%=mod;
        x*=x,x%=mod,y>>=1;
    }
    return s;
}
int f[N],pri[N],tot;
int g[N],inv[N],F[N];
int mu[N];
bool zs[N];
int n,m;
void pre(){
    f[1]=g[1]=F[0]=F[1]=1,mu[1]=1,zs[1]=1;
    for(int i=2;i<=N-5;i++){
        f[i]=(f[i-1]+f[i-2])%mod,g[i]=qpow(f[i],mod-2),F[i]=1;
        if(!zs[i])pri[++tot]=i,mu[i]=-1;
        for(int j=1;j<=tot&&i*pri[j]<=N-5;j++){
            zs[i*pri[j]]=1;
            if(i%pri[j])mu[i*pri[j]]=-mu[i];
            else break;
        }
    }
    for(int i=1;i<=N-5;i++){
        if(!mu[i])continue;
        for(int j=i;j<=N;j+=i)
            F[j]=F[j]*(mu[i]==1?f[j/i]:g[j/i])%mod;
    }
    for(int i=2;i<=N-5;i++)
        F[i]=F[i]*F[i-1]%mod;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T,pre();
    while(T--){
        cin>>n>>m;
        if(n>m)swap(n,m);
        int l=1,r,inv,ans=1;
        while(l<=n){
            r=min(n/(n/l),m/(m/l));
            inv=F[r]*qpow(F[l-1],mod-2)%mod;
            ans=ans*qpow(inv,(n/l)*(m/l)%(mod-1))%mod;
            l=r+1;
        }
        cout<<ans<<"\n";
    }
    return 0;
}