#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e2+5,mod=1e9+7;
int n,m,a[N];
int f[2][N][2005];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1),f[0][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++)
			for(int k=0;k<=m;k++)
				f[i&1][j][k]=0;
		for(int j=0;j<=n;j++){
			int jd=(a[i]-a[i-1])*j,d=a[i]-a[i-1];
			for(int k=0;k<=m;k++){
				if(j&&k>=jd-d)f[i&1][j][k]+=f[(i-1)&1][j-1][k-jd+d];
				if(k>=jd+d)f[i&1][j][k]+=f[(i-1)&1][j+1][k-jd-d]*(j+1)%mod;
				if(k>=jd)f[i&1][j][k]+=f[(i-1)&1][j][k-jd]*(j+1)%mod;
				f[i&1][j][k]%=mod;
			}
		}
	}
	int ans=0;
	for(int i=0;i<=m;i++)
		ans+=f[n&1][0][i],ans%=mod;
	cout<<ans;
}