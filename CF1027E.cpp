#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=505+5,p=998244353;
int f[N][N];
int n,k;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>k;
    int ans=0;
    for(int i=1;i<=n;i++)f[i][i]=1;
    for(int i=2;i<=n;i++){
        for(int j=1;j<i;j++)
            for(int k=i-j;k<i;k++)
                (f[i][j]+=f[k][min(k,j)])%=p;
        f[i][i]+=f[i][i-1];
    }
    for(int i=n;i>=1;i--)f[n][i]-=f[n][i-1],(f[n][i]+=p)%=p;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(i*j<k)(ans+=f[n][i]*f[n][j]%p)%=p;
    cout<<ans*2%p;
    return 0;
}