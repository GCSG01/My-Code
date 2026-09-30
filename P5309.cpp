#include<bits/stdc++.h>
// #define int long long
using namespace std;
constexpr int N=2e5+5,mod=1e9+7;
int bk;
int pre[2000][2000];
int n,m,a[N],sum[N],pos[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m,bk=160;
    for(int i=1;i<=n;i++)cin>>a[i],(sum[pos[i]=i/bk]+=a[i])%=mod;
    while(m--){
        int op,x,y,z,l,r;cin>>op;
        if(op==1){
            cin>>x>>y>>z;
            if(!(y^x))y-=x;
            if(x<=bk)for(;y<x;y++)pre[x][y]=(pre[x][y]+z)%mod;
            else for(;y<=n;y+=x)a[y]=(a[y]+z)%mod,sum[pos[y]]=(sum[pos[y]]+z)%mod;
        }
        else{
            int ans=0;cin>>l>>r;
            if(pos[l]==pos[r])
                for(int i=l;i<=r;i++)
                    ans=(ans+a[i])%mod;
            else{
                for(int i=l;i<pos[l]*bk+bk;i++)ans=(ans+a[i])%mod;
                for(int i=pos[l]+1;i<pos[r];i++)ans=(ans+sum[i])%mod;
                for(int i=pos[r]*bk;i<=r;i++)ans=(ans+a[i])%mod;
            }
            for(int i=1;i<=bk;i++)
                if((l/i)^(r/i)){
                    ans=(ans+(1ll*(r/i)-(l/i)-1)*pre[i][i-1]%mod)%mod,
                    ans=(ans+pre[i][r%i])%mod,
                    ans=(ans+pre[i][i-1])%mod;
                    if(l%i)ans=(ans-pre[i][(l%i)-1])%mod;
                    if(ans<0)ans+=mod;
                }
                else{
                    ans=(ans+pre[i][r%i])%mod;
                    if(l%i)ans=(ans-pre[i][(l%i)-1])%mod;
                    if(ans<0)ans+=mod;
                }
            cout<<ans<<"\n";
        }
    }
}