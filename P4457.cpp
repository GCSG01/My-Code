#include<bits/stdc++.h>
#define int long long
const int N=1.5e3+5,mod=1e9+7;
using namespace std;
int n,p,m,k;
int f[N],a[N][N];
int qpow(int x,int y){
    int s=1;
    while(y){
        if(y&1)s=s*x%mod;
        x=x*x%mod,y>>=1;
    }
    return s;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        cin>>n>>p>>m>>k;
        if(!k){
            cout<<"-1\n";continue;
        }
        if(!m){
            if(k==1){
                cout<<"-1\n";continue;
            }
            int ans=0;
            while(p>0){
                if(p<n)p++;
                p-=k,ans++;
            }
            cout<<ans<<"\n";continue;
        }
        int inv=qpow(m+1,mod-2),in1=qpow(m,mod-2);
        f[0]=qpow(m*inv%mod,k);
        for(int i=1;i<=min(n+1,k);i++)
            f[i]=f[i-1]*in1%mod*qpow(i,mod-2)%mod*(k-i+1)%mod;
        for(int i=1;i<n;i++)
            for(int j=1;j<=i;j++)
                a[i][j]=(f[i-j]*m%mod+f[i-j+1])%mod*inv%mod;
        for(int i=1;i<n;i++)
            a[i][i+1]=f[0]*inv%mod,(a[i][i]+=mod-1)%=mod;
        for(int i=1;i<=n;i++)
            a[i][n+1]=mod-1,a[n][i]=f[n-i];
        (a[n][n]+=mod-1)%mod;
        for(int i=1;i<=n;i++){
            int inv=qpow(a[i][i],mod-2);a[i][i]=1,(a[i][n+1]*=inv)%=mod;
            if(i!=n)(a[i][i+1]*=inv)%=mod;
            for(int j=i+1;j<=n;j++)
                (a[j][i+1]+=mod-a[j][i]*a[i][i+1]%mod)%=mod,
                (a[j][n+1]+=mod-a[j][i]*a[i][n+1]%mod)%=mod,
                a[j][i]=0;
        }
        for(int i=n;i>1;i--)
            (a[i-1][n+1]+=mod-a[i-1][i]*a[i][n+1]%mod)%=mod,a[i-1][i]=0;
        cout<<a[p][n+1]<<"\n";
        for(int i=0;i<=n+1;i++)
            for(int j=0;j<=n+1;j++)
                a[i][j]=0;
        for(int i=1;i<=min(n+1,k);i++)f[i]=0;
    }
    return 0;
}