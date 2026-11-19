#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,q,c[N];
int tot,val[N];
int rk[N],dfn[N],dfntot;
int pdx[]={1,0,-1,0};
int pdy[]={0,1,0,-1};
vector<array<int,3>>e;
vector<array<int,2>>g[N];
int fa[N][22],dep[N],siz[N];
set<int>st[N];
struct BIT{
	int tr[N];
	inline int lowbit(int x){return x&-x;}
	inline void add(int x,int k){
		while(x<=tot)tr[x]+=k,x+=lowbit(x);
	}
	inline int get(int x,int s=0){
		while(x)s+=tr[x],x-=lowbit(x);
		return s;
	}
	inline int query(int val,int r){
		return get(r)-get(val-1);
	}
}tr;
inline int get(int x,int y){return (x-1)*m+y;}
inline void add(int u,int v,int w){
	g[u].push_back({v,w}),g[v].push_back({u,w});
}
inline void build(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int pd=0;pd<4;pd++){
				int x=i+pdx[pd],y=j+pdy[pd];
				if(x<1||y<1||x>n||y>m)continue;
				e.push_back({max(val[get(x,y)],val[get(i,j)]),get(x,y),get(i,j)});
			}
}
void Kruskal(){
	sort(e.begin(),e.end());
	vector<int>fa(n*m*2+500);
	for(int i=1;i<=n*m*2+10;i++)fa[i]=i;
	auto find=[&](auto& self,int x)->int{
		return fa[x]==x?x:fa[x]=self(self,fa[x]);
	};
	for(auto [w,u,v]:e){
		u=find(find,u),v=find(find,v);
		if(u==v)continue;
		fa[u]=fa[v]=++tot,val[tot]=w,add(u,tot,w),add(v,tot,w);
	}
}
void dfs(int x,int ffa){
	fa[x][0]=ffa,dep[x]=dep[ffa]+1,siz[x]=1,rk[dfn[x]=++dfntot]=x;
	for(int i=1;i<=19;i++)
		fa[x][i]=fa[fa[x][i-1]][i-1];
	for(auto y:g[x])
		if(y[0]!=ffa)
			dfs(y[0],x),siz[x]+=siz[y[0]];
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=19;i>=0;i--)
		if(dep[fa[x][i]]>=dep[y])
			x=fa[x][i];
	if(x==y)return x;
	for(int i=19;i>=0;i--)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
void ins(int x) {
	tr.add(dfn[x],1);
	int pre=0,nxt=0;
	auto it=st[c[x]].upper_bound(dfn[x]);
	if(it!=st[c[x]].end())
		nxt=rk[*it],tr.add(dfn[LCA(x,nxt)],-1);
	if(it != st[c[x]].begin())
		pre=rk[*(--it)],tr.add(dfn[LCA(x,pre)],-1);
	if(nxt&&pre)
		tr.add(dfn[LCA(nxt,pre)],1);
	st[c[x]].insert(dfn[x]);
}
void del(int x){
	tr.add(dfn[x],-1);
	int nxt=0,pre=0;
	st[c[x]].erase(dfn[x]);
	auto it=st[c[x]].upper_bound(dfn[x]);
	if(it!=st[c[x]].end())
		nxt=rk[*it],tr.add(dfn[LCA(x,nxt)],1);
	if(it!=st[c[x]].begin())
		pre=rk[*(--it)],tr.add(dfn[LCA(x,pre)],1);
	if(nxt&&pre)
		tr.add(dfn[LCA(nxt,pre)],-1);
}
int query(int p,int v){
	if(val[p]>v)return 0;
	for (int i=20;i>=0;i--)
		if(val[fa[p][i]]<=v)
			p=fa[p][i];
	return tr.query(dfn[p],dfn[p]+siz[p]-1);
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m>>q,tot=n*m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>val[get(i,j)];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>c[get(i,j)];
	build();
	Kruskal();
	val[0]=1e9,dfs(tot,0);
	for(int i=1;i<=n*m;i++)ins(i);
	while(q--){
		int op,x,y,cc;cin>>op>>x>>y>>cc;
		if(op==1)
			del(get(y,x)),c[get(y,x)]=cc,ins(get(y,x));
		else cout<<query(get(y,x),cc)<<"\n";
	}
}