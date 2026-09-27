#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=305,mod=1e9+7;
int f[N][N][N*2];
int n,l[N],r[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    memset(f,0,sizeof f);
    for(int i=1;i<=n;i++)
        cin>>l[i]>>r[i];
    f[0][0][0]=1;
    for(int i=0;i<n;i++)
        for(int j=0;j<=i;j++)
            for(int k=0;k<=i*2;k++){
                int s=f[i][j][k];
                for(int x=l[i+1];x<=r[i+1];x++){
                    if(!x){
                        (f[i+1][j+1][k]+=s)%=mod;
                        if(k>0)(f[i+1][j][k-1]+=s*k)%=mod;
                    }
                    if(x==1){
                        (f[i+1][j+1][k+1]+=s*2)%=mod;
                        if(k>0)(f[i+1][j][k]+=s*2*k%mod)%=mod;
                    }
                    if(x==2){
                        (f[i+1][j+1][k+2]+=s)%=mod;
                        if(k>0)
                            (f[i+1][j][k+1]+=s*k%mod)%=mod;
                        if(j>0)
                            (f[i+1][j][k+1]+=s*2*j%mod)%=mod;
                        if(k>0&&j>0)
                            (f[i+1][j-1][k]+=s*2*(j-1)%mod*k%mod)%mod;
                    }
                }
            }
    cout<<f[n][1][0]<<"\n";
}