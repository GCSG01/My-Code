#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5,inf=-1e18;
int n,q,a[N];
int mx[N<<2],tr[N<<2];
#define ls p<<1
#define rs p<<1|1
#define mid ((l+r)>>1)
int calc(int l,int r,int p,int v){
	if(mx[p]<=v)return (r-l+1)*v;
	if(l==r)return mx[p];
	if(mx[ls]=v)return (mid-l+1)*v+calc(mid+1,r,rs,v);
	return tr[p]-tr[ls]+calc(l,mid,ls,v);
}
inline void push_up(int l,int r,int p){
	mx[p]=max(mx[ls],mx[rs]),tr[p]=tr[ls]+calc(mid+1,r,rs,mx[ls]);
}
void build(int l,int r,int p){
	if(l==r)
		return mx[p]=tr[p]=a[l],void();
	build(l,mid,ls),build(mid+1,r,rs),push_up(l,r,p);
}
void update(int l,int r,int p,int pos,int v){
	if(l==r)
		return mx[p]=tr[p]=v,void();
	if(pos<=mid)update(l,mid,ls,pos,v);
	else update(mid+1,r,rs,pos,v);
	push_up(l,r,p);
}
int query(int l,int r,int p,int ql,int qr,int &now){
	if(qr<l||r<ql)return 0;
	if(ql<=l&&r<=qr){
		int ans=calc(l,r,p,now);
		return now=max(now,mx[p]),ans;
	}
	int ans=0;
	if(ql<=mid)ans+=query(l,mid,ls,ql,qr,now);
	if(qr>mid)ans+=query(mid+1,r,rs,ql,qr,now);
	return ans;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,n,1);
	while(q--){
		int op,x,y,now;cin>>op>>x>>y;
		if(op==1)
			now=-a[x],cout<<query(1,n,1,x,y,now)<<"\n";
		else update(1,n,1,x,y),a[x]=y;
	}
}