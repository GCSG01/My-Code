#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+5;
int n,m;
int a[N][N];
int dp[4][N][N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>a[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            dp[1][i][j]=max(dp[1][i-1][j],dp[1][i][j-1])+a[i][j];
    for(int i=1;i<=n;i++)
        for(int j=m;j>=1;j--)
            dp[2][i][j]=max(dp[2][i-1][j],dp[2][i][j+1])+a[i][j];
    for(int i=n;i>=1;i--)
        for(int j=1;j<=m;j++)
            dp[3][i][j]=max(dp[3][i+1][j],dp[3][i][j-1])+a[i][j];
    for(int i=n;i>=1;i--)
        for(int j=m;j>=1;j--)
            dp[4][i][j]=max(dp[4][i+1][j],dp[4][i][j+1])+a[i][j];
    int ans=0;
    for(int i=2;i<n;i++)
        for(int j=2;j<m;j++)
            ans=max(ans,dp[1][i][j-1]+dp[4][i][j+1]+dp[2][i-1][j]+dp[3][i+1][j]),
            ans=max(ans,dp[1][i-1][j]+dp[4][i+1][j]+dp[3][i][j-1]+dp[2][i][j+1]);
    cout<<ans;
    return 0;
}