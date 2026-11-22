#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+5,mod=998244353;
int n,a[N];
int f[N][N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(a[i]==3&&a[j]==1)return cout<<0,0;
			else if(a[i]==2&&a[j]==0)return cout<<0,0;
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		if(a[i]<=1)
			for(int j=1;j<=n;j++)
				f[i][j]=f[i-1][j-1];
		else
			for(int j=n;j>=0;j--)
				f[i][j]=(f[i-1][j]+f[i][j+1])%mod;
	}
	int ans=0;
	for(int i=0;i<=n;i++)ans+=f[n][i],ans%=mod;
	cout<<ans;
}