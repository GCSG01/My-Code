#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+5,mod=1e9+7;
int x[N],y[N],ans[N],ask[N],n,q;
int qpow(int a,int b){
    int sum=1;
    while(b){
        if(b&1)sum*=a,sum%=mod;
        a*=a,a%=mod,b>>=1;
    }
    return sum;
}
void work1(){
    cin>>n;
    for(int i=1;i<=n;i++)ans[i]=0;
    for(int i=1;i<=n;i++)cin>>x[i]>>y[i];
    for(int i=1;i<=n;i++)
        for(int k=1;k<=n;k++){
            int sum=y[i],cnt1=1,cnt2=1;
            for(int j=1;j<=n;j++)
                if(i!=j)
                    cnt2=cnt2*((x[i]+mod-x[j])%mod)%mod,
                    cnt1=cnt1*((k+mod-x[j])%mod)%mod;
            ans[k]=(ans[k]+sum*cnt1%mod*qpow(cnt2,mod-2)%mod)%mod;
        }
    cout<<n*30<<"\n";
    for(int i=1;i<=n;i++)
        for(int j=0;j<30;j++)
            cout<<((ans[i]>>j)&1);
    return ;
}
void work2(){
    string S;
    int len;
    cin>>n>>q>>len>>S;
    for(int i=1;i<=q;i++)cin>>ask[i];
    for(int i=0;i<S.size();i++)
        if(S[i]=='1')
            y[i/30+1]+=(1<<(i%30));
    for(int i=1;i<=n;i++)x[i]=i;
    for(int i=1;i<=n;i++)
        for(int k=1;k<=q;k++){
            int sum=y[i],cnt1=1,cnt2=1;
            for(int j=1;j<=n;j++)
                if(i!=j)
                    cnt2=cnt2*((x[i]+mod-x[j])%mod)%mod,
                    cnt1=cnt1*((ask[k]+mod-x[j])%mod)%mod;
            ans[k]=(ans[k]+sum*cnt1%mod*qpow(cnt2,mod-2)%mod)%mod;
        }
    for(int k=1;k<=q;k++)
        cout<<ans[k]<<"\n";
    return ;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int t;cin>>t;
    if(t==1)work1();
    else work2();
    return 0;
}