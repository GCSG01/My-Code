#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
struct edge{
	int x,y,w;
}e[N];
int n,m,q;
int val[N],fa[N];
int siz[N],f[N][30];
vector<int>g[N];
int tot;
int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
void Kru(){
	sort(e+1,e+m+1,[](edge A,edge B){
        return A.w<B.w;
    });
	for(int i=1;i<=n*2;i++)
        f[i][0]=fa[i]=i;
	for(int i=1;i<=m;i++){
		int x=find(e[i].x),y=find(e[i].y);
		if(x==y)continue;
		fa[x]=fa[y]=f[x][0]=f[y][0]=++tot;
		g[x].push_back(tot),
        g[y].push_back(tot),
		g[tot].push_back(x),
        g[tot].push_back(y);
		val[tot]=e[i].w;
	}
	return ;
}
void init(){
	for(int j=1;j<=25;j++)
        for(int i=1;i<2*n;i++)
            f[i][j]=f[f[i][j-1]][j-1];
	return ;
}
void dfs(int x){
	if(g[x].size()==1)
		return siz[x]=1,void();
	for(auto i:g[x])
		if(i!=f[x][0])
            dfs(i),siz[x]+=siz[i];
	return ;
}
bool check(int k,int x,int y,int z){
    for(int i=25;i>=0;i--){
        if(val[f[x][i]]<=k)
            x=f[x][i];
        if(val[f[y][i]]<=k)
            y=f[y][i];
    }
	if(x==y)return siz[x]>=z;
	return siz[x]+siz[y]>=z;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m,tot=n;
	for(int i=1;i<=m;i++)
        cin>>e[i].x>>e[i].y,e[i].w=i;
	Kru();
    init();
    dfs(tot);
	cin>>q;
	while(q--){
		int x,y,z;
		cin>>x>>y>>z;
		int l=1,r=m;
		while(l<r){
			int mid=(l+r)>>1;
			if(check(mid,x,y,z))
                r=mid;
			else l=mid+1;
		}
		cout<<l<<"\n";
	}
	return 0;
}