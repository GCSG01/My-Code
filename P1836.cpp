#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=12;
int fac[N],dp[N];
int dig[N],cnt[N];
int solve(int n){
    int tot=0,x=n,ans=0;
    while(x)dig[++tot]=x%10,x/=10;
    for(int i=tot;i>=1;i--){
        for(int j=0;j<=9;j++)
            cnt[j]+=dp[i-1]*dig[i];
        for(int j=0;j<dig[i];j++)
            cnt[j]+=fac[i-1];
        n-=fac[i-1]*dig[i];
        cnt[dig[i]]+=(n+1);
        cnt[0]-=fac[i-1];
    }
    for(int j=0;j<=9;j++)ans+=cnt[j]*j;
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    fac[0]=1;
    for(int i=1;i<=10;i++)
        fac[i]=fac[i-1]*10,dp[i]=dp[i-1]*10+fac[i-1];
    int n;cin>>n;
    cout<<solve(n);
}