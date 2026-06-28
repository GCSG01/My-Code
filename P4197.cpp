#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
struct edge{
	int x,y,w;
}e[N];
bool cmp(edge x,edge y){
	return x.w<y.w;
}
vector<int> v[N];
int n,m,q,cnt,tot,a[N],fa[N],f[N][30],val[N],dfn[N],dep[N],dis[N],l[N],r[N];
int num,tr[N<<6],ls[N<<6],rs[N<<6],rt[N],mp[N];
int find(int x){
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
void kruskal(){
	cnt=n,sort(e+1,e+m+1,cmp);
	for(int i=1;i<=N-5;i++) f[i][0]=fa[i]=i;
	for(int i=1;i<=m;i++){
		int x=find(e[i].x),y=find(e[i].y);
		if(x==y) continue;
		val[++cnt]=e[i].w;
		f[x][0]=f[y][0]=fa[x]=fa[y]=cnt;
		v[x].push_back(cnt),v[y].push_back(cnt);
		v[cnt].push_back(x),v[cnt].push_back(y);
	}
	return ;
}
void init(){
	for(int j=1;j<=25;j++) for(int i=1;i<=cnt;i++) f[i][j]=f[f[i][j-1]][j-1];
	return ;
}
void predfs(int x){
	dep[x]=dis[x]=dep[f[x][0]]+1;
	for(auto i:v[x]){
		if(i==f[x][0]) continue;
		predfs(i),dis[x]=max(dis[x],dis[i]);
	}
	return ;
}
void dfs(int x){
	if(v[x].size()==1){
		dfn[++tot]=a[x],l[x]=tot,r[x]=tot;
		return ;
	}
	int lc=0,rc=0;
	for(auto i:v[x]){
		if(i==f[x][0]) continue;
		if(!lc) lc=i;
		else rc=i;
	}
	if(dis[lc]<dis[rc]) swap(lc,rc);
	dfs(lc),dfs(rc);
	l[x]=l[lc],r[x]=r[rc];
	return ;
}
void pushup(int x){
	tr[x]=tr[ls[x]]+tr[rs[x]];
	return ;
}
void upd(int x,int &y,int l,int r,int pos){
	y=++num,tr[y]=tr[x];
	if(l==r){
		tr[y]++;
		return ;
	}
	int mid=(l+r)>>1;
	if(pos<=mid) rs[y]=rs[x],upd(ls[x],ls[y],l,mid,pos);
	else ls[y]=ls[x],upd(rs[x],rs[y],mid+1,r,pos);
	pushup(y);
	return ;
}
int qry(int x,int y,int l,int r,int k){
	if(l==r) return l;
	int mid=(l+r)>>1,v=tr[rs[y]]-tr[rs[x]];
	if(k<=v) return qry(rs[x],rs[y],mid+1,r,k);
	else return qry(ls[x],ls[y],l,mid,k-v);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int lst=0;
	cin >>n>>m>>q;
	for(int i=1;i<=n;i++) cin >>a[i];
	for(int i=1;i<=m;i++) cin >>e[i].x>>e[i].y>>e[i].w;
	kruskal(),init();
	for(int i=1;i<=cnt;i++){
		if(l[i]) continue;
		int u=find(i);
		predfs(u),dfs(u);
	}
	for(int i=1;i<=n;i++) mp[i]=dfn[i];
	sort(mp+1,mp+n+1);
	int len=unique(mp+1,mp+n+1)-mp-1;
	for(int i=1;i<=n;i++) dfn[i]=lower_bound(mp+1,mp+len+1,dfn[i])-mp;
	for(int i=1;i<=n;i++) upd(rt[i-1],rt[i],1,n,dfn[i]);
	while(q--){
		int x,y,k;
		cin >>x>>y>>k;
		x^=lst,y^=lst,k^=lst;
		for(int i=25;i>=0;i--) if(val[f[x][i]]<=y) x=f[x][i];
		if(r[x]-l[x]+1<k){
			cout <<-1<<"\n",lst=0;
			continue;			
		}
		lst=mp[qry(rt[l[x]-1],rt[r[x]],1,n,k)];
		cout<<lst<<"\n";
	}
	return 0;
}