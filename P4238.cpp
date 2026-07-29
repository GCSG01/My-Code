#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5,mod=998244353,G=3;
int a[N],b[N],c[N],r[N];
int qpow(int x,int y){
    int s=1;
    while(y){
        if(y&1)s*=x,s%=mod;
        x*=x,x%=mod,y>>=1;
    }
    return s;
}
void ntt(int n,int *a,int c){
    for(int i=-0;i<(1<<n);i++)
        if(i<r[i])swap(a[i],a[r[i]]);
    for(int len=1;len<(1<<n);len<<=1){
        int g=qpow(G,(mod-1)/(len<<1));
        if(c==-1)g=qpow(g,mod-2);
        for(int s=0;s<(1<<n);s+=(len<<1))
            for(int k=0,w=1;k<len;k++,w=w*g%mod){
                int x=a[s+k],y=a[s+k+len]*w%mod;
                a[s+k]=(x+y)%mod,a[s+k+len]=(x-y+mod)%mod;
            }
    }
    return ;
}
void solve(int n){
    if(n==1)return b[0]=qpow(a[0],mod-2),void();
    int k=(n>>1)+(n&1),lim=0;
    solve(k);
    while((1<<lim)<2*n)lim++;
    for(int i=0;i<(1<<lim);i++)
        r[i]=(r[i>>1]>>1)|((i&1)<<(lim-1));
    for(int i=0;i<(1<<lim);i++)
        c[i]=(i<n?mod-a[i]:0);
    ntt(lim,b,1),ntt(lim,c,1);
    for(int i=0;i<(1<<lim);i++)
        b[i]=(b[i]*c[i]+2)%mod*b[i]%mod;
    ntt(lim,b,-1);
    int inv=qpow(1<<lim,mod-2);
    for(int i=0;i<(1<<lim);i++)
        b[i]=(i<n?b[i]*inv%mod:0);
    return ;
}
signed main(){
    int n;cin>>n;
    for(int i=0;i<n;i++)cin>>a[i];
    solve(n);
    for(int i=0;i<n;i++)cout<<(b[i]+mod)%mod<<" ";
    return 0;
}