#include<bits/stdc++.h>
using namespace std;
const int N=105;
int d[N],p[N*N];
int n,k,l;
int f[N*N][N];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int t;cin>>t;
    while(t--){
        cin>>n>>k>>l;
        for(int i=1;i<=n;i++)cin>>d[i];
        for(int i=0;i<=k;i++)p[i]=i;
        for(int i=2*k-1;i>=k+1;i--)p[i]=2*k-i;
        for(int i=0;i<=n*k+n;i++)f[i][0]=1;
        for(int i=1;i<=n*k+n;i++)
            for(int j=1;j<=n;j++){
                f[i][j]=0;
                if(d[j]+p[i%(2*k)]<=l)
                    f[i][j]=f[i-1][j]|f[i-1][j-1];
            }
        int ans=0;
        for(int i=1;i<=n*k+n;i++)ans|=f[i][n];
        if(ans)cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}