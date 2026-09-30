#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=205,mod=1e9+7;
int a[N],k,l[N],r[N];
int x[N],y[N];
int ni[N][N];
int pre[N],suf[N];
int jc[N],inv[N];
int T,n,m;
int qpow(int x,int y){
    int s=1;
    while(y){
        if(y&1)s*=x,s%=mod;
        x*=x,x%=mod,y>>=1;
    }
    return s;
}
int solve(int nx){
    nx%=mod;
    int ans=0;
    pre[0]=1,suf[k+3]=1;
    for(int i=1;i<=k+2;i++)pre[i]=pre[i-1]*(nx-i)%mod;
    for(int i=k+2;i>=1;i--)suf[i]=suf[i+1]*(nx-i)%mod;
    for(int i=1;i<=k+2;i++){
        int sum=pre[i-1]*suf[i+1]%mod*y[i]%mod;
        ans+=sum*qpow(jc[i-1]*((k-i)&1?-1:1)*jc[k+2-i]%mod,mod-2)%mod,ans%=mod;
    }
    if(ans<0)ans+=mod;
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>T;
    jc[0]=1;
    for(int i=1;i<=N-5;i++)jc[i]=jc[i-1]*i%mod;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=m;i++)cin>>a[i];
        sort(a+1,a+m+1);
        a[0]=0,a[m+1]=n+1;
        int tot=0;
        for(int i=1;i<=m+1;i++)
            if(a[i]-a[i-1]-1)
                l[++tot]=a[i-1]+1,r[tot]=a[i]-1;
        r[0]=-1,k=0;
        for(int i=1;i<=tot;i++)
            k+=l[i]-r[i-1]-1;
        for(int i=1;i<=k+2;i++)
            x[i]=i,y[i]=(qpow(i,k)+y[i-1])%mod;
        int ans=0,cnt=0;
        for(int i=1;i<=tot;i++){
            while(a[cnt+1]<l[i])cnt++;
            for(int j=0;j<=cnt;j++)
                (ans+=solve(r[i]-a[j])-solve(l[i]-a[j]-1))%=mod;
        }
        if(ans<0)ans+=mod;
        cout<<ans<<"\n";
    }
    return 0;
}