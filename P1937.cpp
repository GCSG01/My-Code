#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
struct node{
	int l,r;
}a[N];
int n,m;
int tr[N<<2],tag[N<<2];
#define ls p<<1
#define rs p<<1|1
#define mid ((l+r)>>1)
inline void upd(int p,int k){
	tr[p]+=k,tag[p]+=k;
}
void push_down(int p){
	if(!tag[p])return ;
	upd(ls,tag[p]),upd(rs,tag[p]),tag[p]=0;
}
void build(int l,int r,int p){
	if(l==r)
		return cin>>tr[p],void();
	build(l,mid,ls),build(mid+1,r,rs),tr[p]=min(tr[ls],tr[rs]);
}
void update(int l,int r,int p,int ql,int qr,int k){
	if(ql<=l&&r<=qr)
		return upd(p,k);
	push_down(p);
	if(ql<=mid)update(l,mid,ls,ql,qr,k);
	if(qr>mid)update(mid+1,r,rs,ql,qr,k);
	tr[p]=min(tr[ls],tr[rs]);
}
int query(int l,int r,int p,int ql,int qr){
	if(ql<=l&&r<=qr)return tr[p];
	int mn=1e9;
	push_down(p);
	if(ql<=mid)mn=min(mn,query(l,mid,ls,ql,qr));
	if(qr>mid)mn=min(mn,query(mid+1,r,rs,ql,qr));
	return mn;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>m>>n,build(1,m,1);
	for(int i=1;i<=n;i++)cin>>a[i].l>>a[i].r;
	sort(a+1,a+n+1,[](node A,node B){return A.r<B.r;});
	int ans=0;
	for(int i=1;i<=n;i++)
		if(query(1,m,1,a[i].l,a[i].r)>0)ans++,update(1,m,1,a[i].l,a[i].r,-1);
	cout<<ans;
}