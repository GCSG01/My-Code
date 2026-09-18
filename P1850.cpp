#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+5;
int c[N],d[N],dis[305][305];
double g[N],dp[N][N][2];
int n,m,v,e;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>v>>e;
    memset(dis,0x3f,sizeof(dis));
    for(int i=1;i<=n;i++)cin>>c[i];
    for(int i=1;i<=n;i++)cin>>d[i];
    for(int i=1;i<=n;i++)cin>>g[i];
    for(int i=1,u,v,w;i<=e;i++)
        cin>>u>>v>>w,dis[u][v]=dis[v][u]=min(dis[u][v],w);
    for(int k=1;k<=v;k++)
        for(int i=1;i<=v;i++)
            for(int j=1;j<=v;j++)
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
    for(int i=1;i<=v;i++)dis[i][i]=0;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++)
            dp[i][j][0]=dp[i][j][1]=1145141919;
    dp[1][0][0]=dp[1][1][1]=0;
    for(int i=2;i<=n;i++){
        int c1=c[i-1],d1=d[i-1],c2=c[i],d2=d[i];
        dp[i][0][0]=dp[i-1][0][0]+dis[c1][c2];
        for(int j=1;j<=min(i,m);j++)
            dp[i][j][0]=min(dp[i-1][j][0]+dis[c1][c2],dp[i-1][j][1]+dis[c1][c2]*(1-g[i-1])+dis[d1][c2]*g[i-1]),
            dp[i][j][1]=min(dp[i-1][j-1][0]+dis[c1][c2]*(1-g[i])+dis[c1][d2]*g[i],
                            dp[i-1][j-1][1]+(dis[c1][c2]*(1-g[i-1])+dis[d1][c2]*g[i-1])*(1-g[i])+
                            (dis[c1][d2]*(1-g[i-1])+dis[d1][d2]*g[i-1])*g[i]);
    }
	double ans=1145141919;
	for(int i=0;i<=m;i++)
		ans=min(ans,min(dp[n][i][0],dp[n][i][1]));
	printf("%.2lf",ans);
    return 0;
}