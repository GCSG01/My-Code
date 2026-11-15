#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,m,cnt;
struct node{
	int col,v,ls,rs;
}tr[N*40];
int vis[N],dep[N],fa[N][20],a[N],ans[N],rt[N];
vector<int>g[N];
#define ls(p) tr[(p)].ls
#define rs(p) tr[(p)].rs
#define mid ((l+r)>>1)
void pushup(int p){
	if(tr[ls(p)].v>=tr[rs(p)].v)
        tr[p].v=tr[ls(p)].v,tr[p].col=tr[ls(p)].col;
	else tr[p].v=tr[rs(p)].v,tr[p].col=tr[rs(p)].col;
	if(tr[p].v<=0)tr[p].col=0;
}
void upd(int &p,int l,int r,int pos,int k){
	if(!p)p=++cnt;
	if(l==pos&&pos==r)
		return tr[p].v+=k,tr[p].col=l,void();
	if(pos<=mid)upd(ls(p),l,mid,pos,k);
	else upd(rs(p),mid+1,r,pos,k);
	pushup(p);
}
int merge(int x,int y,int l,int r){
	if(!x||!y)return x+y;
	int z=++cnt;
	if(l==r)return tr[z].v=tr[x].v+tr[y].v,tr[z].col=l,z;
	tr[z].ls=merge(ls(x),ls(y),l,mid),tr[z].rs=merge(rs(x),rs(y),mid+1,r);
	return pushup(z),z;
}
void dfs(int x,int ffa){
    fa[x][0]=ffa,dep[x]=dep[ffa]+1;
    for(int i=1;i<=18;i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    for(int y:g[x])
        if(y!=ffa)
            a[x]++,dfs(y,x);
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=18;i>=0;i--)
		if(dep[fa[x][i]]>=dep[y])
			x=fa[x][i];
	if(x==y)return x;
	for(int i=18;i>=0;i--)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1,u,v;i<n;i++)
		cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	dfs(1,0);
	for(int i=1,x,y,z;i<=m;i++){
		cin>>x>>y>>z;
		int k=LCA(x,y);
		upd(rt[x],1,N-5,z,1);
		upd(rt[y],1,N-5,z,1);
		upd(rt[k],1,N-5,z,-1);
		upd(rt[fa[k][0]],1,N-5,z,-1);
	}
	for(int i=1;i<=n;i++)
		if(!vis[i]){
			int j=i;
			while(!a[j])
				ans[j]=tr[rt[j]].col,rt[fa[j][0]]=merge(rt[j],rt[fa[j][0]],1,N-5),
				vis[j]=1,a[fa[j][0]]--,j=fa[j][0];
		}
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<"\n";
}