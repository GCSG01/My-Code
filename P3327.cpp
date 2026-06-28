#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
const int N=5e4+5;
int mu[N],p[N],tot,vis[N];
int sum[N],s[N];
void init(){
    mu[1]=1;
    for(int i=2;i<=N-4;i++){
        if(!vis[i])
            p[++tot]=i,mu[i]=-1;
        for(int j=1;j<=tot&&p[j]*i<=N-4;j++){
            vis[p[j]*i]=1;
            if(i%p[j])
                mu[p[j]*i]=-mu[i];
            else break;
        }
    }
    for(int i=1;i<=N-4;i++)
        sum[i]=sum[i-1]+mu[i];
    for(int i=1;i<=N-4;i++){
        int ans=0;
        for(int l=1,r;l<=i;l=r+1)
            r=i/(i/l),ans+=(r-l+1)*(i/l);
        s[i]=ans;
    }
    return ;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    init();
    while(T--){
        int n,m;cin>>n>>m;
        if(n>m)swap(n,m);
        int ans=0;
        for(int l=1,r;l<=n;l=r+1){
            r=min(n/(n/l),m/(m/l));
            // cout<<l<<" "<<r<<" "<<ans<<"\n";
            // cout<<sum[r]-sum[l-1]<<" "<<s[n/l]<<" "<<s[m/l]<<"\n";
            ans+=(sum[r]-sum[l-1])*s[n/l]*s[m/l];
        }
        cout<<ans<<"\n";
    }
    return 0;
}