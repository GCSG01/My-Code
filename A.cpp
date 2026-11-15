#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=7e5+5,inf=4e18;
int n,q,S,K;
bitset<N>vis;
struct node{
	int v,w,id;
};
vector<node>g[N];
struct query{
	int t,x,id;
}qu[N];
vector<int>ev[N];
array<int,3>par[N];
int et[N],ed[N];
int ord[N],dfn[N],dep[N],tot;
vector<pair<int,int>>ask[N];
int ans[N];
namespace Segment_Tree{
	struct node{
		int val,tag,hval,htag;
	}tr[N<<2];
	#define ls (p<<1)
	#define rs (p<<1|1)
	#define mid ((l+r)>>1)
	inline void push_up(int p){
		tr[p].val=min(tr[ls].val,tr[rs].val),tr[p].hval=min(tr[ls].hval,tr[rs].hval);
	}
	inline void upd(int p,int val,int tag){
		if(tag<inf)
			tr[p].hval=min(tr[p].hval,tr[p].val+tag),
			tr[p].htag=min(tr[p].htag,tr[p].tag+tag);
		tr[p].val+=val,tr[p].tag+=val;
	}
	inline void push_down(int p){
		if(!tr[p].tag&&tr[p].htag>=inf)return ;
		upd(ls,tr[p].tag,tr[p].htag),upd(rs,tr[p].tag,tr[p].htag),tr[p].tag=0,tr[p].htag=inf;
	}
	void build(int l,int r,int p){
		tr[p]={0,0,inf,inf};
		if(l==r)return ;
		build(l,mid,ls),build(mid+1,r,rs);
	}
	void update(int l,int r,int p,int ql,int qr,int x){
		if(ql>qr)return ;
		if(ql<=l&&r<=qr)
			return upd(p,x,inf);
		push_down(p);
		if(ql<=mid)update(l,mid,ls,ql,qr,x);
		if(qr>mid)update(mid+1,r,rs,ql,qr,x);
		push_up(p);
	}
	void reset(int l,int r,int p,int ql,int qr){
		if(ql>qr)return ;
		if(ql<=l&&r<=qr)
			return upd(p,0,0);
		push_down(p);
		if(ql<=mid)reset(l,mid,ls,ql,qr);
		if(qr>mid)reset(mid+1,r,rs,ql,qr);
		push_up(p);
	}
	int get(int l,int r,int p,int x){
		if(l==r)return tr[p].hval;
		push_down(p);
		if(x<=mid)return get(l,mid,ls,x);
		return get(mid+1,r,rs,x);
	}
	#undef ls
	#undef rs
	#undef mid
}
using Segment_Tree::build;
using Segment_Tree::update;
using Segment_Tree::reset;
using Segment_Tree::get;
void dfs(int x){
	ord[++tot]=x,dfn[x]=tot;
	for(auto e:g[x])
		if(e.v!=par[x][0])
			par[e.v]={x,e.id,e.w},dep[e.v]=dep[x]+e.w,dfs(e.v);
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	freopen("val.in","r",stdin);
	freopen("val.out","w",stdout);
	cin>>n>>q>>S>>K;
	for(int i=1,u,v,w;i<n;i++)
		cin>>u>>v>>w,g[u].push_back({v,w,i}),g[v].push_back({u,w,i});
	for(int i=1;i<=q;i++)
		cin>>qu[i].t>>qu[i].x,qu[i].x=max(qu[i].x,1ll),qu[i].id=i;
	par[S]={0,0,0},dfs(S);
	for(int i=n;i>=1;i--){
		int x=ord[i];ed[x]=dfn[x];
		for(auto e:g[x])
			if(par[e.v][0]==x)
				ed[x]=max(ed[x],ed[e.v]);
	}
	for(int i=1;i<=n;i++){
		int x=i;
		while(x!=S&&!vis[par[x][1]]){
			int id=par[x][1];
			vis[id]=1,et[id]=i;
			ev[i].push_back(x),x=par[x][0];
		}
	}
	build(1,n,1);
	for(int x=1;x<=n;x++)
		if(x!=S){
			int l=dfn[x],r=ed[x],w=par[x][2];
			if(et[par[x][1]])
				update(1,n,1,1,l-1,2*w),update(1,n,1,r+1,n,2*w);
		}
	for(int x=1;x<=n;x++)
		update(1,n,1,dfn[x],dfn[x],dep[x]-K*n);
	for(int i=1;i<=q;i++)
		ask[min(qu[i].x,n+1)].push_back({qu[i].t,i});
	update(1,n,1,1,n,-K);
	reset(1,n,1,1,n);
	for(auto [t,id]:ask[n+1])
		ans[id]=get(1,n,1,dfn[t]);
	for(int i=n;i>=1;i--){
		update(1,n,1,1,n,K);
		for(int x:ev[i]){
			int l=dfn[x],r=ed[x],w=par[x][2];
			update(1,n,1,1,l-1,-2*w),update(1,n,1,r+1,n,-2*w);
		}
		if(i!=S&&(par[i][1]==0||et[par[i][1]]>=i))
			reset(1,n,1,1,dfn[i]-1),reset(1,n,1,ed[i]+1,n);
		for(auto [t,id]:ask[i])ans[id]=get(1,n,1,dfn[t]);
	}
	for(int i=1;i<=q;i++)cout<<ans[i]<<'\n';
}