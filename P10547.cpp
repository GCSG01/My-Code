#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=505,M=5e3+5,B=75,mod=1e9+7;
int n,m;
int dp[2][B][M][2];
int Ans[M];
vector<pair<int,int>>qu[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	for(int i=1;i<=T;i++)
		cin>>n>>m,qu[n].push_back({m,i});
	dp[0][0][0][0]=1;
	for(int I=0,i=0;I<=500;I++,i^=1){
		memset(dp[i^1],0,sizeof(dp[i^1]));
		for(int j=0;j<=71;j++)
			for(int p=j*(j-1)/2;p+j*(j+1)/2<=5000;p++)
				for(int op=0;op<2;op++){
					int x=dp[i][j][p][op];
					(dp[i^1][j+1][p+j][op]+=x)%=mod;
					(dp[i^1][j][p+j][op^1]+=x)%=mod;
					(dp[i^1][j][p+j][op]+=x*j)%=mod;
					(dp[i^1][j][p+j][op]+=x*j)%=mod;
					if(j)
						(dp[i^1][j-1][p+j][op]+=x*j*(j-1))%=mod,
						(dp[i^1][j-1][p+j][op^1]+=x*j)%=mod;
				}
		for(auto [m,id]:qu[I])
			for(int p=0;p<=m;p++)
				Ans[id]+=dp[i][0][p][0],Ans[id]%=mod;
	}
	for(int i=1;i<=T;i++)
		cout<<Ans[i]<<"\n";
}