#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,a[N];
#define ls p<<1
#define rs p<<1|1
#define mid ((l+r)>>1)
int tr[N<<2];
inline int merge(int a,int b){
	if(a==-2||b==-2)return -2;
	if(a==-1&&b==-1)return -1;
	if(a==-1)return b;
	if(b==-1)return a;
	if(a==b)return a;
	return -2;
}
void build(int l,int r,int p){
	if(l==r)
		return cin>>tr[p],void();
	build(l,mid,ls),build(mid+1,r,rs),tr[p]=merge(tr[ls],tr[rs]);
}
void update(int l,int r,int p,int x,int k){
	if(l==r)
		return tr[p]=k,void();
	if(x<=mid)update(l,mid,ls,x,k);
	else update(mid+1,r,rs,x,k);
	tr[p]=merge(tr[ls],tr[rs]);
}
int query(int l,int r,int p,int ql,int qr){
	if(ql<=l&&r<=qr)return tr[p];
	if(qr<=mid)return query(l,mid,ls,ql,qr);
	if(ql>mid)return query(mid+1,r,rs,ql,qr);
	return merge(query(l,mid,ls,ql,qr),query(mid+1,r,rs,ql,qr));
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int q;cin>>n>>q,build(1,n,1);
	while(q--){
		int op,l,r;cin>>op>>l>>r;
		if(op==1)update(1,n,1,l,r);
		else cout<<(query(1,n,1,l,r)==-2?"No\n":"Yes\n");
	}
}