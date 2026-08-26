#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e3+5,p=1e9+7;
int n,a[N];
int f[N][N];
int qpow(int x,int y){
    int s=1;
    while(y){
        if(y&1)s*=x,s%=p;
        x*=x,x%=p,y>>=1;
    }
    return s;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int q,t;
    cin>>n>>q,t=q;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            f[i][j]=(a[i]<a[j]);
    int inv=qpow(2,p-2);
    while(t--){
        int u,v;cin>>u>>v;
        for(int i=1;i<=n;i++)
            if(i!=u&&i!=v)
                f[i][u]=f[i][v]=(f[i][u]+f[i][v])%p*inv%p,
                f[u][i]=f[v][i]=(f[u][i]+f[v][i])%p*inv%p;
        f[u][v]=f[v][u]=(f[u][v]+f[v][u])%p*inv%p;
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<i;j++)
            ans+=f[i][j],ans%=p;
    cout<<(ans*qpow(2,q)%p);
    return 0;
}