#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,inf=1e18;
int n,a[N];
int dep[N],dfn[N],dfntot,son[N],siz[N];
int val[N],fa[N],top[N],idx[N];
vector<array<int,2>>g[N];
namespace tree{
	struct node{
		int mx,mn,sum,tag;
	}tr[N<<2];
	#define ls (p<<1)
	#define rs (p<<1|1)
	#define mid ((l+r)>>1)
	inline node merge(node x,node y){
		return {max(x.mx,y.mx),min(x.mn,y.mn),x.sum+y.sum,0};
	}
	inline void upd(int p){
		swap(tr[p].mn,tr[p].mx),tr[p].mn*=-1,tr[p].mx*=-1,tr[p].sum*=-1,tr[p].tag^=1;
	}
	inline void push_down(int p){
		if(tr[p].tag)upd(ls),upd(rs);
		tr[p].tag=0;
	}
	void build(int l,int r,int p){
		if(l==r)
			return tr[p]={val[idx[l]],val[idx[l]],val[idx[l]],0},void();
		build(l,mid,ls),build(mid+1,r,rs),tr[p]=merge(tr[ls],tr[rs]);
	}
	void update(int l,int r,int p,int x,int k){
		if(l==r)
			return tr[p]={k,k,k,0},void();
		push_down(p);
		if(x<=mid)update(l,mid,ls,x,k);
		if(x>mid)update(mid+1,r,rs,x,k);
		tr[p]=merge(tr[ls],tr[rs]);
	}
	void cover(int l,int r,int p,int ql,int qr){
		if(ql>qr)return ;
		if(ql<=l&&r<=qr)
			return upd(p);
		push_down(p);
		if(ql<=mid)cover(l,mid,ls,ql,qr);
		if(qr>mid)cover(mid+1,r,rs,ql,qr);
		tr[p]=merge(tr[ls],tr[rs]);
	}
	node query(int l,int r,int p,int ql,int qr){
		if(ql>qr)return {-inf,inf,0,0};
		if(ql<=l&&r<=qr)
			return tr[p];
		push_down(p);
		if(qr<=mid)return query(l,mid,ls,ql,qr);
		if(ql>mid)return query(mid+1,r,rs,ql,qr);
		return merge(query(l,mid,ls,ql,qr),query(mid+1,r,rs,ql,qr));
	}
	#undef ls
	#undef rs
	#undef mid
}
void dfs1(int x,int ffa){
	dep[x]=dep[ffa]+1,fa[x]=ffa,siz[x]=1;
	for(auto [y,w]:g[x])
		if(y!=ffa)
			val[y]=w,dfs1(y,x),siz[x]+=siz[y],son[x]=siz[y]>siz[son[x]]?y:son[x];
}
void dfs2(int x,int Top){
	dfn[x]=++dfntot,top[x]=Top,idx[dfntot]=x;
	if(son[x])dfs2(son[x],top[x]);
	for(auto [y,w]:g[x])
		if(y!=fa[x]&&y!=son[x])
			dfs2(y,y);
}
void cover(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		tree::cover(1,n,1,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y])swap(x,y);
	tree::cover(1,n,1,dfn[y]+1,dfn[x]);
}
tree::node query(int x,int y){
	tree::node ans={-inf,inf,0,0};
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans=tree::merge(ans,tree::query(1,n,1,dfn[top[x]],dfn[x]));
		x=fa[top[x]];
	}
	if(dep[x]<dep[y])swap(x,y);
	ans=tree::merge(ans,tree::query(1,n,1,dfn[y]+1,dfn[x]));
	return ans;
}
array<int,2>ed[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1,u,v,w;i<n;i++)
		cin>>u>>v>>w,u++,v++,g[u].push_back({v,w}),g[v].push_back({u,w}),ed[i]={u,v};
	dfs1(1,0),dfs2(1,1),tree::build(1,n,1);
	int q;cin>>q;
	while(q--){
		string op;cin>>op;
		if(op=="C"){
			int i,w;cin>>i>>w;
			auto [u,v]=ed[i];
			if(dep[u]<dep[v])swap(u,v);
			tree::update(1,n,1,dfn[u],w);
		}
		else if(op=="N"){
			int u,v;cin>>u>>v,u++,v++,cover(u,v);
		}
		else{
			int u,v;cin>>u>>v,u++,v++;
			tree::node ans=query(u,v);
			if(op=="SUM")cout<<ans.sum<<"\n";
			if(op=="MAX")cout<<ans.mx<<"\n";
			if(op=="MIN")cout<<ans.mn<<"\n";
		}
	}
}