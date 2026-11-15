#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e2+5;
int mod,n,K;
int f[2][N][N][N];
int sum[N][N][N];
void build(int op){
	for(int l=0;l<n;l++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				sum[i][j][l]=sum[i-1][j][l]+sum[i][j-1][l]-sum[i-1][j-1][l]+f[op][i][j][l],
				sum[i][j][l]=(sum[i][j][l]%mod+mod)%mod;
}
int query(int x1,int y1,int x2,int y2,int l){
	int res=sum[x2][y2][l]-sum[x1-1][y2][l]-sum[x2][y1-1][l]+sum[x1-1][y1-1][l];
	return (res%mod+mod)%mod;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>K>>mod;
	f[1][1][1][0]=1;
	for(int op=2;op<=n;op++){
		int i=op&1;build((op-1)&1);
		for(int j=1;j<=op;j++)
			for(int k=1;k<=op;k++)
				for(int l=0;l<op;l++){
					f[i][j][k][l]=query(1,k,j-1,n,l)+query(j,1,n,k-1,l);
					if(l)f[i][j][k][l]+=query(1,1,j-1,k-1,l-1)+query(j,k,n,n,l-1);
					f[i][j][k][l]%=mod;
				}
	}
	int ans=0;
	for(int j=1;j<=n;j++)
		for(int k=1;k<=n;k++)
			ans+=f[n&1][j][k][K],ans%=mod;
	cout<<ans;
}