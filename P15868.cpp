#include<bits/stdc++.h> 
#define int long long
using namespace std;
const int N=5e2+5;
int n,a[N];
int dp[N][N];
int vis[N];
int Ans[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int t;cin>>t>>t;
    while(t--){
        cin>>n,vis[0]=0;
        for(int i=1;i<=n;i++)
            cin>>a[i],a[i]=min(a[i],n),vis[i]=0;
        for(int i=0;i<=n;i++){
            Ans[i]=0;
            for(int j=0;j<=n;j++)
                dp[i][j]=-1e18;
        }
        dp[0][0]=0;
        for(int t=1;t<=n;t++){
            vis[a[t]]++;
            int mx=a[t]+1;
            while(vis[mx])mx++;
            for(int i=0;i<=n;i++)
                dp[i][mx]=max(dp[i][a[t]],dp[i][mx]);
            for(int j=0;j<=n;j++){
                int cnt=0;
                for(int i=1;i<=t;i++)
                    if(a[i]<j)cnt++;
                cnt-=j;
                if(cnt<=0)continue;
                int mx=j+1;
                while(vis[mx])mx++;
                for(int i=0;i<=n;i++)
                    if(dp[i][j]>=0)
                        dp[i+1][mx]=max(dp[i][j],dp[i+1][mx]);
            }
            for(int i=0;i<=n;i++)
                for(int j=0;j<=n;j++)
                    dp[i][j]+=j;
        }
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++)
                Ans[i]=max(Ans[i],dp[i][j]);
            if(i)Ans[i]=max(Ans[i],Ans[i-1]);
        }
        for(int i=0;i<=n;i++)
            cout<<Ans[i]<<" ";
        cout<<"\n";
    }
}