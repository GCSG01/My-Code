#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,a[N];
int dep[N],dfn[N],dfntot,son[N],siz[N];
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
			return tr[p]={a[l],a[l],a[l],0},void();
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
		if(ql<=l&&r<=qr)
			return upd(p);
		push_down(p);
		if(ql<=mid)cover(l,mid,ls,ql,qr);
		if(qr>mid)cover(mid+1,r,rs,ql,qr);
		tr[p]=merge(tr[ls],tr[rs]);
	}
	node query(int l,int r,int p,int ql,int qr){
		if(ql<=l&&r<=qr)
			return tr[p];
		push_down(p);
		if(qr<=mid)return query(l,mid,ls,ql,qr);
		if(ql>mid)return query(mid+1,r,rs,ql,qr);
		return merge(query(l,mid,ls,ql,qr),query(mid+1,r,rs,ql,qr));
	}
}
void dfs(int x,int fa){		
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1,u,v,w;i<n;i++)
		cin>>u>>v>>w,g[u].push_back({v,w}),g[v].push_back({u,w});
	dfs(1,0);
}