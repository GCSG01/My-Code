#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=15;
int len[N];
int fac[N],dp[N];
int cnta[N],cntb[N];
void solve(int now,int *cnt){
    int tot=0,x=now;
    while(x)
        len[++tot]=x%10,x/=10;
    for(int i=tot;i>=1;i--){
        for(int j=0;j<=9;j++)
            cnt[j]+=dp[i-1]*len[i];
        for(int j=0;j<len[i];j++)
            cnt[j]+=fac[i-1];
        now-=fac[i-1]*len[i];
        cnt[len[i]]+=(now+1);
        cnt[0]-=fac[i-1];
    }
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int a,b;cin>>a>>b;
    fac[0]=1;
    for(int i=1;i<=13;i++)
        fac[i]=fac[i-1]*10,dp[i]=dp[i-1]*10+fac[i-1];
    solve(b,cntb),solve(a-1,cnta);
    for(int i=0;i<=9;i++)
        cout<<cntb[i]-cnta[i]<<" ";
}