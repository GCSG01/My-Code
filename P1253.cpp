#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,inf=1e18;
int n,m,a[N];
struct node{
    int cov,tag,mx;
}tr[N<<2];
#define ls p<<1
#define rs p<<1|1
#define mid ((l+r)>>1)
inline void push_up(int p){
    tr[p].mx=max(tr[ls].mx,tr[rs].mx);
}
inline void upd(int p,int cov,int tag){
    if(cov==-inf&&tag==-inf)return;
    if(cov==-inf){
        if(tr[p].tag==-inf)tr[p].tag=tag;
        else tr[p].tag+=tag;
        tr[p].mx+=tag;
        return;
    }
    if(tag==-inf)
        return tr[p].cov=cov,tr[p].tag=-inf,tr[p].mx=cov,void();
    tr[p].cov=cov,tr[p].tag=tag,tr[p].mx=cov+tag;
}
inline void push_down(int p){
    upd(ls,tr[p].cov,tr[p].tag),upd(rs,tr[p].cov,tr[p].tag),tr[p].cov=tr[p].tag=-inf;
}
void build(int l,int r,int p){
    tr[p]={-inf,-inf,0};
    if(l==r)
        return tr[p]={-inf,-inf,a[l]},void();
    build(l,mid,ls),build(mid+1,r,rs),push_up(p);
}
void cover(int l,int r,int p,int s,int t,int k){
    if(s<=l&&r<=t)
        return upd(p,k,0);
    push_down(p);
    if(s<=mid)cover(l,mid,ls,s,t,k);
    if(t>mid)cover(mid+1,r,rs,s,t,k);
    push_up(p);
}
void update(int l,int r,int p,int s,int t,int k){
    if(s<=l&&r<=t){
        if(tr[p].tag==-inf)tr[p].tag=k;
        else tr[p].tag+=k;
        tr[p].mx+=k;
        return;
    }
    push_down(p);
    if(s<=mid)update(l,mid,ls,s,t,k);
    if(t>mid)update(mid+1,r,rs,s,t,k);
    push_up(p);
}
int query(int l,int r,int p,int s,int t){
    if(s<=l&&r<=t)
        return tr[p].mx;
    int mx=-inf;push_down(p);
    if(s<=mid)mx=max(mx,query(l,mid,ls,s,t));
    if(t>mid)mx=max(mx,query(mid+1,r,rs,s,t));
    return mx;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    build(1,n,1);
    while(m--){
        int op,l,r,x;cin>>op>>l>>r;
        if(op==1)cin>>x,cover(1,n,1,l,r,x);
        else if(op==2)cin>>x,update(1,n,1,l,r,x);
        else cout<<query(1,n,1,l,r)<<"\n";
    }
}