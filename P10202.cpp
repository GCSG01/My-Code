#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=55,p=1e9+7;
int f[N][N][N],g[N][N][N];
int fac[N],inv[N];
int a[N],n;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n,fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<=52;i++)fac[i]=fac[i-1]*i%p,inv[i]=(p-p/i)*inv[p%i]%p;
    for(int i=0;i<=n+1;i++)f[i][i][1]=g[i][i][0]=1;
    for(int i=1;i<=n;i++)cin>>a[i];
	for(int l=n;l>=0;l--)
        for(int r=l+1;r<=n+1;r++){
            int len=r-l;
            for(int i=l+1;i<=r;i++)
                if(a[i]==a[r])
                    for(int j=0;j<=len;j++)
                        for(int k=1;j+k<=len;k++)
                            (g[l][r][j+k]+=g[l][i-1][j]*f[i][r][k]%p)%=p;
            if(a[l]!=a[r])continue;
            for(int i=0;i<=len;i++)
                (g[l][r][i]+=g[l][r-1][i])%=p;
            for(int i=0;i<len;i++)
                f[l][r][i+1]=inv[i+1]*g[l][r-1][i]%p;
        }
    int ans=0;
	for(int i=1;i<=n+1;i++)
        (ans+=f[0][n+1][i]*fac[i]%p)%=p;
	cout<<ans;
    return 0;
}