#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
const int p=998244353,N=3e5+5;
int n;
int f[N],g[N];
int inv[N],jc[N];
int power(int a,int b){
    int s=1;
    while(b){
        if(b&1)s*=a,s%=p;
        a*=a,a%=p,b>>=1;
    }
    return s;
}
int C(int n,int m){
    return jc[n]*inv[m]%p*inv[n-m]%p;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    f[0]=f[1]=1;
    for(int i=2;i<=N-5;i++)
        f[i]=f[i-1]+f[i-2]*(i-1)%p,f[i]%=p;
    g[0]=1;
    for(int i=1;i<=N-5;i++)
        g[i]=g[i-1]*(2*i-1)%p*2%p;

    jc[0]=jc[1]=1;
    for(int i=2;i<=N-5;i++)
        jc[i]=jc[i-1]*i%p;

    inv[N-5]=power(jc[N-5],p-2),inv[0]=1;
    for(int i=N-6;i>=1;i--)
        inv[i]=inv[i+1]*(i+1)%p;
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        int ans=0;
        for(int i=0;i*4<=n;i++){
            // cout<<C(n-2*i,2*i)<<" "<<g[i]<<" "<<f[n-4*i]<<"\n";
            ans=ans+C(n-2*i,2*i)*g[i]%p*f[n-4*i]%p,ans%=p;
        }
        cout<<ans<<"\n";
    }
    return 0;
}