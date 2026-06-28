#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int cnt;
int col[N<<6],tr[N<<6],ls[N<<6],rs[N<<6];
int vis[N],dep[N],fa[N][20],num[N],ans[N],rt[N];
vector<int>g[N];
void pushup(int x){
	if(tr[ls[x]]>=tr[rs[x]])
        tr[x]=tr[ls[x]],col[x]=col[ls[x]];
	else tr[x]=tr[rs[x]],col[x]=col[rs[x]];
	if(tr[x]<=0)col[x]=0;
	return ;
}
void upd(int &x,int l,int r,int pos,int k){
	if(!x)x=++cnt;
	if(l==pos&&pos==r)
		return tr[x]+=k,col[x]=l,void();
	int mid=(l+r)>>1;
	if(pos<=mid)upd(ls[x],l,mid,pos,k);
	else upd(rs[x],mid+1,r,pos,k);
	pushup(x);
	return ;
}
int merge(int x,int y,int l,int r){
	if(!x||!y) return x+y;
	int mid=(l+r)>>1,z=++cnt;
	if(l==r)return tr[z]=tr[x]+tr[y],col[z]=l,z;
	ls[z]=merge(ls[x],ls[y],l,mid),rs[z]=merge(rs[x],rs[y],mid+1,r);
	pushup(z);
	return z;
}
void dfs(int x,int ffa){
    fa[x][0]=ffa,dep[x]=dep[ffa]+1;
    for(int i=1;i<=18;i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    for(int y:g[x])
        if(y!=ffa)
            num[x]++,dfs(y,x);
    return ;
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	int k=dep[x]-dep[y];
	for(int i=18;i>=0;i--)
        if((1<<i)<=k)
            k-=(1<<i),x=fa[x][i];
	if(x==y)return x;
	for(int i=18;i>=0;i--)
        if(fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int n,m;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1,x,y;i<n;i++)
		cin>>x>>y,g[x].push_back(y),g[y].push_back(x);
	dfs(1,0);
	for(int i=1,x,y,z;i<=m;i++){
		cin>>x>>y>>z;
		int k=lca(x,y);
		upd(rt[x],1,N-5,z,1);
		upd(rt[y],1,N-5,z,1);
		upd(rt[k],1,N-5,z,-1);
		upd(rt[fa[k][0]],1,N-5,z,-1);
	}
	for(int i=1;i<=n;i++)
		if(!vis[i]){
            int j=i;
            while(num[j]==0){
                ans[j]=col[rt[j]];
                rt[fa[j][0]]=merge(rt[j],rt[fa[j][0]],1,N-5);
                vis[j]=1,num[fa[j][0]]--,j=fa[j][0];
            }
        }
	for(int i=1;i<=n;i++)
        cout<<ans[i]<<"\n";
	return 0;
}