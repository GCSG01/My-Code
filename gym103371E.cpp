#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=65,K=1e3+5;
int n,k;
int p,c[N],w[N];
int mn[N][K][K];
int mx[N][K][K];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>k>>p;
	for(int i=1;i<=n;i++)cin>>c[i]>>w[i];
	memset(mn,0x3f,sizeof mn);
	memset(mx,-0x3f,sizeof mx);
	mn[n+1][k][0]=mx[n+1][k][0]=0;
	for(int i=n;i>=1;i--){
		for(int j=0;j<=k;j++)
			for(int t=0;t<=j;t++){
				int x=c[i+1]/c[i]*t+p/c[i];
				if(x<=j)
					mn[i][j][x]=min(mn[i][j][x],mn[i+1][j][t]),
					mx[i][j][x]=max(mx[i][j][x],mx[i+1][j][t]);
			}
		for(int j=k;j;j--)
			for(int t=j;t;t--)
				mn[i][j-1][t-1]=min(mn[i][j-1][t-1],mn[i][j][t]+w[i]),
				mx[i][j-1][t-1]=max(mx[i][j-1][t-1],mx[i][j][t]+w[i]);
		p%=c[i];
	}
	if(mx[1][0][0]<0)cout<<"-1";
	else cout<<mn[1][0][0]<<" "<<mx[1][0][0];
}