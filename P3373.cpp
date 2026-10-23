#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int mod;
namespace Segment_Tree{
	struct node{
		int v,mul,add;
	}tr[N<<2];
	#define ls (p<<1)
	#define rs (p<<1|1)
	#define mid ((l+r)>>1)
	inline void push_up(int p){
		tr[p].v=(tr[ls].v+tr[rs].v)%mod;
	}
	inline void upd(int l,int r,int p,int mul,int add){
		tr[p].v=(mul*tr[p].v%mod+add*(r-l+1)%mod)%mod,
		tr[p].mul=(mul*tr[p].mul)%mod,tr[p].add=(mul*tr[p].add+add)%mod;
	}
	inline void push_down(int l,int r,int p){
		upd(l,mid,ls,tr[p].mul,tr[p].add),upd(mid+1,r,rs,tr[p].mul,tr[p].add),tr[p].mul=1,tr[p].add=0;
	}
	void build(int l,int r,int p){
		tr[p].mul=1;
		if(l==r)
			return cin>>tr[p].v,void();
		build(l,mid,ls),build(mid+1,r,rs),push_up(p);
	}
	void update(int l,int r,int p,int ql,int qr,int mul,int add){
		if(ql<=l&&r<=qr)
			return upd(l,r,p,mul,add);
		push_down(l,r,p);
		if(ql<=mid)update(l,mid,ls,ql,qr,mul,add);
		if(qr>mid)update(mid+1,r,rs,ql,qr,mul,add);
		push_up(p);
	}
	int query(int l,int r,int p,int ql,int qr){
		if(ql<=l&&r<=qr)
			return tr[p].v;
		int sum=0;push_down(l,r,p);
		if(ql<=mid)sum+=query(l,mid,ls,ql,qr);
		if(qr>mid)sum+=query(mid+1,r,rs,ql,qr);
		return sum%mod;
	}
}
using Segment_Tree::build;
using Segment_Tree::update;
using Segment_Tree::query;
int n,q;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>q>>mod,build(1,n,1);
	while(q--){
		int op,l,r,k;cin>>op>>l>>r;
		if(op==1)
			cin>>k,update(1,n,1,l,r,k%mod,0);
		else if(op==2)
			cin>>k,update(1,n,1,l,r,1,k%mod);
		else cout<<query(1,n,1,l,r)<<"\n";
	}
}