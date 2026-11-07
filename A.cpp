#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=7e5+5,inf=4e18;
int n,q,S,K,dfn[N],ed[N],df[N],tmr;
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
int et[N];
vector<pair<int,int>>ask[N];
int ans[N];
struct Seg{
	struct node{
		int val,tag,hval,htag;
	}tr[N<<2];
	#define ls (p<<1)
	#define rs (p<<1|1)
	#define mid ((l+r)>>1)
	inline void pushup(int p){
		tr[p].val=min(tr[ls].val,tr[rs].val),tr[p].hval=min(tr[ls].hval,tr[rs].hval);
	}
	inline void upd(int p,int val,int tag){
		if(tag<inf)tr[p].hval=min(tr[p].hval,tr[p].val+tag);
		tr[p].val+=val;
		if(tag<inf)tr[p].htag=min(tr[p].htag,tr[p].tag+tag);
		tr[p].tag+=val;
	}
	void pushdown(int p){
		if(tr[p].tag||tr[p].htag<inf){
			upd(ls,tr[p].tag,tr[p].htag);
			upd(rs,tr[p].tag,tr[p].htag);
			tr[p].tag=0;tr[p].htag=inf;
		}
	}
	void build(int p,int l,int r){
		tr[p]={0,0,inf,inf};
		if(l==r)return;
		build(ls,l,mid);build(rs,mid+1,r);
	}
	void add(int p,int l,int r,int L,int R,int x){
		if(L>R)return;
		if(L<=l&&r<=R){upd(p,x,inf);return;}
		pushdown(p);
		if(L<=mid)add(ls,l,mid,L,R,x);
		if(R>mid)add(rs,mid+1,r,L,R,x);
		pushup(p);
	}
	void record(int p,int l,int r,int L,int R){
		if(L>R)return;
		if(L<=l&&r<=R){upd(p,0,0);return;}
		pushdown(p);
		if(L<=mid)record(ls,l,mid,L,R);
		if(R>mid)record(rs,mid+1,r,L,R);
		pushup(p);
	}
	int get(int p,int l,int r,int x){
		if(l==r)return tr[p].hval;
		pushdown(p);
		if(x<=mid)return get(ls,l,mid,x);
		return get(rs,mid+1,r,x);
	}
	#undef ls
	#undef rs
	#undef mid
}seg;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	freopen("val.in","r",stdin);
	freopen("val.out","w",stdout);
	cin>>n>>q>>S>>K;
	for(int i=1,u,v,w;i<n;i++)
		cin>>u>>v>>w,g[u].push_back({v,w,i}),g[v].push_back({u,w,i});
	for(int i=1;i<=q;i++)
		cin>>qu[i].t>>qu[i].x,qu[i].x=max(qu[i].x,1ll),qu[i].id=i;
	vector<int>order;order.reserve(n);
	vector<int>st={S};par[S]={0,0,0};
	while(!st.empty()){
		int x=st.back();st.pop_back();
		dfn[x]=++tmr;order.push_back(x);
		for(auto e:g[x])if(e.v!=par[x][0]){
			par[e.v]={x,e.id,e.w};df[e.v]=df[x]+e.w;
			st.push_back(e.v);
		}
	}
	for(int i=n-1;i>=0;i--){
		int x=order[i];ed[x]=dfn[x];
		for(auto e:g[x])
			if(par[e.v][0]==x)
				ed[x]=max(ed[x],ed[e.v]);
	}
	for(int i=1;i<=n;i++){
		int x=i;
		while(x!=S&&!vis[par[x][1]]){
			int id=par[x][1];vis[id]=1;et[id]=i;
			ev[i].push_back(x);
			x=par[x][0];
		}
	}
	seg.build(1,1,n);
	for(int x=1;x<=n;x++)if(x!=S){
		int l=dfn[x],r=ed[x],w=par[x][2];
		if(et[par[x][1]])
			seg.add(1,1,n,1,l-1,2*w),seg.add(1,1,n,r+1,n,2*w);
	}
	for(int x=1;x<=n;x++)
		seg.add(1,1,n,dfn[x],dfn[x],df[x]-K*n);
	for(int i=1;i<=q;i++)
		ask[min(qu[i].x,n+1)].push_back({qu[i].t,i});
	seg.add(1,1,n,1,n,-K);
	seg.record(1,1,n,1,n);
	for(auto [t,id]:ask[n+1])
		ans[id]=seg.get(1,1,n,dfn[t]);
	for(int i=n;i>=1;i--){
		seg.add(1,1,n,1,n,K);
		for(int child:ev[i]){
			int l=dfn[child],r=ed[child],w=par[child][2];
			seg.add(1,1,n,1,l-1,-2*w),seg.add(1,1,n,r+1,n,-2*w);
		}
		if(i!=S&&(par[i][1]==0||et[par[i][1]]>=i))
			seg.record(1,1,n,1,dfn[i]-1),seg.record(1,1,n,ed[i]+1,n);
		for(auto [t,id]:ask[i])ans[id]=seg.get(1,1,n,dfn[t]);
	}
	for(int i=1;i<=q;i++)cout<<ans[i]<<'\n';
}