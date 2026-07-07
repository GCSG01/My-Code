#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=21;
int n;
int d[N][N];
int f[N][1<<N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>d[i][j];
    memset(f,0x3f,sizeof f);
    for(int i=1;i<=n;i++)f[i][1<<(i-1)]=d[1][i];
    for(int s=0;s<(1<<n);s++)
        for(int i=1;i<=n;i++)
            if((s&(1<<(i-1))))
                for(int j=1;j<=n;j++)
                    if(s&1<<(j-1)){
                        f[i][s]=min(f[i][s],f[j][s^(1<<(i-1))]+d[j][i]);
                    }
    int ans=INT_MAX;
    for(int i=1;i<=n;i++)
        ans=min(ans,f[i][(1<<n)-1]+d[i][1]);
    cout<<ans;
    return 0;
}