#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5;
int n,q,W;
int v[N],w[N];
int f[2][N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>q>>W;
    for(int i=1;i<=q;i++){
        int x,y,z;cin>>x>>y>>z;
        for(int j=0;j<=15;j++)
            if(z>=(1<<j))
                v[++n]=x*(1<<j),w[n]=y*(1<<j),z-=(1<<j);
        if(z)v[++n]=x*z,w[n]=y*z;
    }
    for(int i=1;i<=n;i++){
        memset(f[i&1],0,sizeof f[i&1]);
        for(int j=0;j<=W;j++){
            f[i&1][j]=max(f[i&1][j],f[(i-1)&1][j]);
            if(j>=w[i])
                f[i&1][j]=max(f[i&1][j],f[(i-1)&1][j-w[i]]+v[i]);
        }
    }
    int ans=0;
    for(int i=0;i<=W;i++)ans=max(ans,f[n&1][i]);
    cout<<ans;
}