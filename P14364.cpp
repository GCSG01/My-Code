#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=505,mod=998244353;
int n,m,s[N],c[N];
int cnt[N],pre[N];
int C[N][N],fac[N];
int f[N][N],nf[N][N];
inline int get(){
    char c;cin>>c;return c-'0';
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)s[i]=get();
    for(int i=1;i<=n;i++)cin>>c[i],cnt[c[i]]++;
    pre[0]=cnt[0];
    for(int i=1;i<=n;i++)pre[i]=pre[i-1]+cnt[i];
    for(int i=0;i<=n;i++){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    }
    fac[0]=1;
    for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    f[0][0]=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++)
            for(int k=0;k<=i;k++){
                if(!f[j][k])continue;
                int now=f[j][k];
                if(s[i+1]){
                    (nf[j][k+1]+=now)%=mod;
                    for(int w=0;w<=min(k,cnt[j+1]);w++)
                        if(pre[j]>i-k){
                            int sum=C[cnt[j+1]][w]*C[k][w]%mod*fac[w]%mod;
                            (nf[j+1][k-w]+=now*sum%mod*(pre[j]-i+k))%=mod;
                        }
                }
                else{
                    for(int w=0;w<=min(k,cnt[j+1]);w++){
                        int sum=C[cnt[j+1]][w]*C[k][w]%mod*fac[w]%mod;
                        (nf[j+1][k-w+1]+=now*sum%mod)%=mod;
                        if(pre[j+1]>i-k+w)
                            (nf[j+1][k-w]+=now*sum%mod*(pre[j+1]-i+k-w))%=mod;
                    }
                }
            }
        memcpy(f,nf,sizeof f);
        memset(nf,0,sizeof nf);
    }
    int ans=0;
    for(int j=0;j<=n-m;j++)
        if(n>=pre[j])(ans+=f[j][n-pre[j]]*fac[n-pre[j]]%mod)%=mod;
    cout<<ans;
}