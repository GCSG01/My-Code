#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m;
struct node{
    int pre,suf,mx,s0,tag,len;
}tr[N<<2];
#define ls p<<1
#define rs p<<1|1
#define mid ((l+r)>>1)
node merge(node A,node B){
    node C;
    C.pre=A.pre,C.suf=B.suf;
    if(C.pre==A.len)C.pre+=B.pre;
    if(C.suf==B.len)C.suf+=A.suf;
    C.mx=max({A.mx,B.mx,A.suf+B.pre});
    C.s0=A.s0+B.s0;
    C.tag=0,C.len=A.len+B.len;
    return C;
}
void upd(int l,int r,int p,int val){
    tr[p].tag=val;
    if(val==1)tr[p].s0=tr[p].suf=tr[p].pre=tr[p].mx=0;
    else tr[p].s0=tr[p].pre=tr[p].suf=tr[p].mx=r-l+1;
}
void push_down(int l,int r,int p){
    if(!tr[p].tag)return ;
    upd(l,mid,ls,tr[p].tag),upd(mid+1,r,rs,tr[p].tag),tr[p].tag=0;
}
void build(int l,int r,int p){
    if(l==r)
        return tr[p]={0,0,0,0,0,1},void();
    build(l,mid,ls),build(mid+1,r,rs);
    tr[p]=merge(tr[ls],tr[rs]);
}
void update(int l,int r,int p,int s,int t,int val){//-1=all 0,1=all 1
    if(s<=l&&r<=t)
        return upd(l,r,p,val);
    push_down(l,r,p);
    if(s<=mid)update(l,mid,ls,s,t,val);
    if(t>mid)update(mid+1,r,rs,s,t,val);
    tr[p]=merge(tr[ls],tr[rs]);
}
node query(int l,int r,int p,int s,int t){
    if(t<s)return {0,0,0,0,0,0};
    if(s<=l&&r<=t)return tr[p];
    push_down(l,r,p);
    if(t<=mid)return query(l,mid,ls,s,t);
    if(s>mid)return query(mid+1,r,rs,s,t);
    node A=query(l,mid,ls,s,t),B=query(mid+1,r,rs,s,t);
    return merge(A,B);
}
int get(int l,int r,int p,int k){
    if(l==r)return l;
    push_down(l,r,p);
    if(tr[ls].s0>=k)return get(l,mid,ls,k);
    else return get(mid+1,r,rs,k-tr[ls].s0);
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m,build(1,n,1);
    while(m--){
        int op,l,r;cin>>op>>l>>r;
        if(!op)
            update(1,n,1,l,r,-1);
        else if(op==1){
            int x,y;cin>>x>>y;
            int s=r-l+1-query(1,n,1,l,r).s0;
            update(1,n,1,l,r,-1);
            s+=query(1,n,1,1,x-1).s0;
            if(!s)continue;
            int pos=get(1,n,1,s);
            update(1,n,1,x,min(y,pos),1);
        }
        else cout<<query(1,n,1,l,r).mx<<"\n";
    }
    return 0;
}