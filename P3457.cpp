#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
int n,m,a[N][N],f[N][N];
int pdx[]={1,0,-1,0};
int pdy[]={0,1,0,-1};
int fa[N*N],vis[N*N];
struct node{
	int x,y,h;
}b[N*N];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y)return ;
	fa[x]=y,vis[y]|=vis[x];
}
int get(int x,int y){return (x-1)*m+y;}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;memset(a,0x3f,sizeof a);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			if(a[i][j]<0)
				a[i][j]=-a[i][j];
			else f[i][j]=1;
			b[get(i,j)]={i,j,a[i][j]};
			fa[get(i,j)]=get(i,j);
		}
	sort(b+1,b+get(n,m)+1,[](node a,node b){return a.h<b.h;});
	int ans=0;
	for(int i=1;i<=n*m;i++){
		for(int j=0;j<4;j++){
			int nx=b[i].x+pdx[j],ny=b[i].y+pdy[j];
			if(a[nx][ny]<=b[i].h)
				merge(get(nx,ny),get(b[i].x,b[i].y));
		}
		if(b[i].h!=b[i+1].h)
			for(int j=i;;j--){
				if(b[j].h!=b[i].h)break;
				if(f[b[j].x][b[j].y]){
					int x=find(get(b[j].x,b[j].y));
					if(!vis[x])vis[x]=1,ans++;
				}
			}
	}
	cout<<ans;
}