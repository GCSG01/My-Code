#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,B,q,a[N],sum[N];
int tr[N<<2],tag[N<<2];
#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
inline void push_up(int p){
	tr[p]=max(tr[ls],tr[rs]);
}
inline void upd(int p,int k){
	tag[p]+=k,tr[p]+=k;
}
inline void push_down(int p){
	if(!tag[p])return ;
	upd(ls,tag[p]),upd(rs,tag[p]),tag[p]=0;
}
void build(int l,int r,int p){
	if(l==r)
		return tr[p]=sum[l],void();
	build(l,mid,ls),build(mid+1,r,rs),push_up(p);
}
void update(int l,int r,int p,int ql,int qr,int v){
	if(ql<=l&&r<=qr)
		return upd(p,v),void();
	push_down(p);
	if(ql<=mid)update(l,mid,ls,ql,qr,v);
	if(qr>mid)update(mid+1,r,rs,ql,qr,v);
	push_up(p);
}
double query(int l,int r,int p){
	if(l==r)
		return tr[p]*1.0/l+B;
	push_down(p);
	if(tr[ls]>=0)return query(l,mid,ls);
	return query(mid+1,r,rs);
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>B>>q;
	for(int i=1;i<=n;i++)
		cin>>a[i],sum[i]=sum[i-1]+a[i]-B;
	build(1,n,1);
	while(q--){
		int c,x;cin>>c>>x;
		update(1,n,1,c,n,x-a[c]),a[c]=x;
		printf("%.10lf\n",query(1,n,1));
	}
}