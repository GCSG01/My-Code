#include<bits/stdc++.h>
#define int long long
using namespace std;
const int M=1e3+5,N=1e6+5,mod=1e9+7;
vector<int>g[N];
int n,m;
int in[N],out[N];
int f[N][5],a[M][M];
int pdx[]={0,0,1,-1},pdy[]={1,-1,0,0};
inline int get(int x,int y){return (x-1)*m+y;}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=0;k<4;k++){
				int x=i+pdx[k],y=j+pdy[k];
				if(x<1||x>n||y<1||y>m)continue;
				if(a[x][y]==a[i][j]+1)
					g[get(i,j)].emplace_back(get(x,y)),in[get(x,y)]++,out[get(i,j)]++;
			}
	queue<int>s;
	for(int i=1;i<=n*m;i++)
		if(!in[i])s.push(i),f[i][1]=1;
	while(!s.empty()){
		int u=s.front();
		s.pop();
		for(int v:g[u]){
			for(int i=2;i<=4;i++)
				f[v][i]=(f[v][i]+f[u][i-1])%mod;
			f[v][4]=(f[v][4]+f[u][4])%mod;
			if(!--in[v])s.push(v);
		}
	}
	int ans=0;
	for(int i=1;i<=n*m;i++)
		if(!out[i])ans=(ans+f[i][4])%mod;
	cout<<ans;
}