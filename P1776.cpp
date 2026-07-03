#include<bits/stdc++.h>
using namespace std;
const int N=105;
int v[N],w[N],m[N];
int dp[N][40005];
int n,W;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>W;
    for(int i=1;i<=n;i++)
        cin>>v[i]>>w[i]>>m[i];
    for(int i=1;i<=n;i++)
        for(int k=0;k<=m[i];k++)
            for(int j=k*w[i];j<=W;j++)
                dp[i][j]=max(dp[i][j],
                    dp[i-1][j-k*w[i]]+k*v[i]);
    cout<<dp[n][W];
    return 0;
}