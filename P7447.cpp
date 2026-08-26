#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e5+5,B=10,P=14,G=8,inf=1e9;
int n,m,a[N];
int MN,MX,s,t,L[N],w,v;
ll lans;
struct node{
    int mn,mx,siz,tag;
    ll v;
}tr[G][200055];
#define ls p<<1
#define rs p<<1|1
#define mid ((l+r)>>1)
inline int get(int x){
    return upper_bound(L,L+G,x)-L-1;
}
inline void upd(int w,int p,int v){
    tr[w][p].mx-=!!tr[w][p].siz*v,
    tr[w][p].mn-=!!tr[w][p].siz*v,
    tr[w][p].v-=(ll)tr[w][p].siz*v,tr[w][p].tag+=v;
}
inline node merge(node A,node B){
    node C;
    C.mx=max(A.mx,B.mx),C.mn=min(A.mn,B.mn);
    C.siz=A.siz+B.siz,C.v=A.v+B.v;
    return C;
}
void push_down(int w,int p){
    if(!tr[w][p].tag)return ;
    upd(w,ls,tr[w][p].tag),upd(w,rs,tr[w][p].tag),tr[w][p].tag=0;
}
void bdown(int w,int l,int r,int v){
    if(!v)return;
    for(int i=l;i<=r;i++)
        if(L[w]<=a[i]&&a[i]<L[w+1])a[i]-=v;
}
void bup(int w,int p,int l,int r){
    tr[w][p].siz=tr[w][p].mx=tr[w][p].v=0,tr[w][p].mn=inf;
    for(int i=l;i<=r;i++)
        if(L[w]<=a[i]&&a[i]<L[w+1])
            tr[w][p].siz++,tr[w][p].v+=a[i],
            tr[w][p].mx=max(tr[w][p].mx,a[i]),
            tr[w][p].mn=min(tr[w][p].mn,a[i]);
}
void ins(int w,int p,int l,int r,int x,int v){
    if(r-l<B){
        bdown(w,l,r,tr[w][p].tag),tr[w][p].tag=0;
        return a[x]=v,bup(w,p,l,r);
    }
    push_down(w,p);
    if(x<=mid)ins(w,ls,l,mid,x,v); 
    else ins(w,rs,mid+1,r,x,v);
    tr[w][p]=merge(tr[w][ls],tr[w][rs]);
}
inline void bupd(int w,int l,int r,int v){
    for(int i=l;i<=r;i++)
        if(L[w]<=a[i]&&a[i]<L[w+1]&&a[i]>v){
            a[i]-=v;
            if(a[i]<L[w]) 
                ins(get(a[i]),1,1,n,i,a[i]);
        }
}
inline void bquery(int w,int l,int r){
    for(int i=l;i<=r;i++)
        if(L[w]<=a[i]&&a[i]<L[w+1])
            lans+=a[i],MN=min(MN,a[i]),MX=max(MX,a[i]);
}
void update(int p,int l,int r){
	if(tr[w][p].mx<=v)return;
	if(s<=l&&r<=t&&tr[w][p].mn-v>=L[w])
        return upd(w,p,v);
	if(r-l<B){
		bdown(w,l,r,tr[w][p].tag);
        tr[w][p].tag=0;
		bupd(w,max(l,s),min(r,t),v);
        bup(w,p,l,r);
        return;
	}
	push_down(w, p);
	if(s<=mid)update(ls,l,mid);
	if(t>mid)update(rs,mid+1,r);
    tr[w][p]=merge(tr[w][ls],tr[w][rs]);
}
void query(int p, int l, int r){
	if(!tr[w][p].siz)return;
	if(s<=l&&r<=t)
        return lans+=tr[w][p].v,MN=min(MN,tr[w][p].mn),MX=max(MX,tr[w][p].mx),void();
	if(r-l<B){
		bdown(w,l,r,tr[w][p].tag);
        tr[w][p].tag=0;
		bquery(w,max(l,s),min(r,t));
        return;
	}
	push_down(w, p);
	if(s<=mid)query(ls,l,mid);
	if(t>mid)query(rs,mid+1,r);
}
void build(int p,int l,int r){
    if(r-l<B)return bup(w,p,l,r);
    build(ls,l,mid),build(rs,mid+1,r);
    tr[w][p]=merge(tr[w][ls],tr[w][rs]);
}
int main(){
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin>>n>>m,L[0]=1;
    for(int i=1;i<=G;i++)L[i]=L[i-1]*P;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(w=0;w<G;w++)build(1,1,n);
    ll lastans=0;
    while(m--){
		int op;cin>>op>>s>>t;
        s^=lastans,t^=lastans;
		if(op&1){
			cin>>v,v^=lastans;
			for(w=0;w<G;w++)update(1,1,n);
		}
		else{
			lans=MX=0,MN=1e9;
			for(w=0;w<G;w++)query(1,1,n);
            cout<<lans<<" "<<MN<<" "<<MX<<"\n";
            lastans=lans&((1LL<<20)-1);
		}
	}
	return 0;
}