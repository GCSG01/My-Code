#include<bits/stdc++.h>
using namespace std;
const int N=5e4+5;
int n,m;
struct node{
	int lx,rx,mx,tag;
}tr[N<<2];
#define ls p<<1
#define rs p<<1|1
#define mid ((l+r)>>1)
inline void upd(int l,int r,int p,int k){
	if(k==1)
		tr[p].mx=tr[p].lx=tr[p].rx=0;
	else if(k==2)tr[p].mx=tr[p].lx=tr[p].rx=r-l+1;
	tr[p].tag=k;
}
inline void push_down(int l,int r,int p){
	if(tr[p].tag)upd(l,mid,ls,tr[p].tag),upd(mid+1,r,rs,tr[p].tag);
	tr[p].tag=0;
}
inline void push_up(int l,int r,int p){
	tr[p].mx=max({tr[ls].mx,tr[rs].mx,tr[ls].rx+tr[rs].lx});
	tr[p].lx=tr[ls].lx,tr[p].rx=tr[rs].rx;
	if(tr[ls].lx==mid-l+1)
		tr[p].lx=tr[ls].lx+tr[rs].lx;
	if(tr[rs].rx==r-mid)
		tr[p].rx=tr[rs].rx+tr[ls].rx;
}
void build(int l,int r,int p){
	tr[p].lx=tr[p].rx=tr[p].mx=r-l+1;
	if(l==r)return ;
	build(l,mid,ls),build(mid+1,r,rs);
}
int query(int l,int r,int p,int x){
	// cout<<l<<" "<<r<<" "<<p<<" "<<x<<" "<<tr[p].mx<<"\n";
	if(l==r)return l;
	push_down(l,r,p);
	if(tr[ls].mx>=x)return query(l,mid,ls,x);
	// cout<<l<<" "<<r<<": "<<tr[ls].rx<<" "<<tr[rs].lx<<"\n";
	if(tr[ls].rx&&tr[ls].rx+tr[rs].lx>=x)return mid-tr[ls].rx+1;
	return query(mid+1,r,rs,x);
}
void update(int l,int r,int p,int ql,int qr,int k){
	if(ql<=l&&r<=qr)
		return upd(l,r,p,k);
	push_down(l,r,p);
	if(ql<=mid)update(l,mid,ls,ql,qr,k);
	if(qr>mid)update(mid+1,r,rs,ql,qr,k);
	push_up(l,r,p);
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m,build(1,n,1);
	while(m--){
		int op,x,y;cin>>op>>x;
		if(op==1){
			if(tr[1].mx<x){cout<<"0\n";continue;}
			int pos=query(1,n,1,x);
			cout<<pos<<"\n",update(1,n,1,pos,pos+x-1,1);
		}
		else cin>>y,update(1,n,1,x,x+y-1,2);
	}
}