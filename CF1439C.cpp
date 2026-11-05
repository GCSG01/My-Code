#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int n,q,a[N];
int tr[N<<2],mn[N<<2],tag[N<<2];
#define ls p<<1
#define rs p<<1|1
#define mid ((l+r)>>1)
inline void push_up(int p){
	tr[p]=tr[ls]+tr[rs],mn[p]=min(mn[ls],mn[rs]);
}
inline void upd(int l,int r,int p,int k){
	tr[p]=(r-l+1)*k,mn[p]=k,tag[p]=k;
}
inline void push_down(int l,int r,int p){
	if(!tag[p])return ;
	upd(l,mid,ls,tag[p]),upd(mid+1,r,rs,tag[p]),tag[p]=0;
}
void build(int l,int r,int p){
	if(l==r)
		return tr[p]=mn[p]=a[l],void();
	build(l,mid,ls),build(mid+1,r,rs),push_up(p);
}
int query(int l,int r,int p,int x,int &v){
	if(r<x||v<mn[p])return 0;
	if(l>=x&&v>=tr[p])
		return v-=tr[p],min(n,r)-l+1;
	push_down(l,r,p);
	int ans=0;
	if(mid>=x)ans+=query(l,mid,ls,x,v);
	return ans+=query(mid+1,r,rs,x,v);
}
int find(int l,int r,int p,int v){
	if(l==r)
		return v>tr[p]?l:l+1;
	push_down(l,r,p);
	if(mn[ls]>=v)return find(mid+1,r,rs,v);
	return find(l,mid,ls,v);
}
void update(int l,int r,int p,int ql,int qr,int v){
	if(ql<=l&&r<=qr)
		return upd(l,r,p,v);
	push_down(l,r,p);
	if(ql<=mid)update(l,mid,ls,ql,qr,v);
	if(qr>mid)update(mid+1,r,rs,ql,qr,v);
	push_up(p);
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,n,1);
	while(q--){
		int op,x,y;cin>>op>>x>>y;
		if(op==1){
			int pos=find(1,n,1,y);
			if(pos<=x)update(1,n,1,pos,x,y);
		}
		else cout<<query(1,n,1,x,y)<<"\n";
	}
}