#include<bits/stdc++.h>
// #define int long long
using namespace std;
const int MAXN=3e3+5,p=998244353;
int power(long long x,int y){
    long long s=1;
    while(y){
        if(y&1)s*=x,s%=p;
        x*=x,x%=p,y>>=1;
    }
    return s;
}
long long f[MAXN][MAXN];
long long jc[MAXN],inv[MAXN];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int N;cin>>N;
    jc[0]=1;
    for(int i=1;i<=N;i++)jc[i]=jc[i-1]*2ll%p;
    for(int i=1;i<=N;i++)inv[i]=power(jc[i],p-2);
    f[1][1]=1;
    for(int n=2;n<=N;n++){
        long long cnt=jc[n]%p*power(jc[n]-1,p-2)%p;
        for(int i=2;i<=n;i++)
            f[n][1]=(f[n][1]+f[n-1][n-i+1]*inv[i]%p)%p;
        f[n][1]*=cnt,f[n][1]%=p;
        for(int i=2;i<=n;i++)
            f[n][i]=(f[n][i-1]*inv[1]%p+f[n-1][i-1]*inv[1]%p)%p;
    }
    for(int i=1;i<=N;i++)
        cout<<f[N][i]<<" ";
    return 0;
}