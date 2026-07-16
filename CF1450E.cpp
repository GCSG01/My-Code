#include<bits/stdc++.h>
using namespace std;
const int N=205,M=2e3+5;
int n,m;
int col[N],flag=0;
int dis[N][N];
vector<int>e[N];
void add(int x,int y,int v){
    e[x].push_back(y),dis[x][y]=v;
}
void dfs(int x,int cc){
    if(!col[x])col[x]=cc;
    else flag=1;
    for(auto y:e[x])
        if(!col[y]||col[y]==cc)
            dfs(y,cc^1);
    return ;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    memset(dis,0x3f,sizeof dis);
    for(int i=1;i<=n;i++)dis[i][i]=0;
    for(int i=1,u,v,b;i<=m;i++){
        cin>>u>>v>>b;
        if(b)add(u,v,1),add(v,u,-1);
        else add(u,v,1),add(v,u,1);
    }
    dfs(1,0);
    if(flag)return cout<<"NO",0;
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
    int ans=-n-1,pos=0;
    for(int i=1;i<=n;i++){
        if(dis[i][i]<0)
			return cout<<"NO",0;
		int mx=-n-1;
		for (int j=1;j<=n;j++)
            mx=max(mx,dis[i][j]);
		if (mx>ans)ans=mx,pos=i;
    }
    cout<<"YES\n";
	cout<<ans<<"\n";
	for (int i=1;i<=n;i++)
        cout<<dis[pos][i]<<" ";
    return 0;
}