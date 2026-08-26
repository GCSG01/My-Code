#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+5;
int n,A,B,a[N];
int f[N][N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>A>>B;
	for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)
        for(int j=0;j<=n;j++)
            f[i][j]=1e18;
	f[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<a[i];j++)
			f[i][j]=f[i-1][j]+A,
            f[i][a[i]]=min(f[i][a[i]],f[i-1][j]);
		for(int j=a[i]+1;j<=n;j++)
			f[i][j]=f[i-1][j]+B;
	}
    int ans=1e18;
	for(int i=0;i<=n;i++)
        ans=min(ans,f[n][i]);
	cout<<ans;
	return 0;
}