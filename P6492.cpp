#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int a[N],n;
namespace Segment_Tree{
    struct node{
        int pre,suf,mx,l,r;
    }tr[N<<2];
    #define ls (p<<1)
    #define rs (p<<1|1)
    #define mid ((l+r)>>1)
    inline node merge(node A,node B){
        node C={};
        C.mx=max(A.mx,B.mx),C.pre=A.pre,C.suf=B.suf,C.l=A.l,C.r=B.r;
        if(a[A.r]!=a[B.l]){
            C.mx=max(C.mx,A.suf+B.pre);
            if(A.pre==A.r-A.l+1)C.pre=A.r-A.l+1+B.pre;
            if(B.suf==B.r-B.l+1)C.suf=B.r-B.l+1+A.suf;
        }
        return C;
    }
    void build(int l,int r,int p){
        if(l==r)
            return tr[p]={1,1,1,l,r},void();
        build(l,mid,ls),build(mid+1,r,rs),tr[p]=merge(tr[ls],tr[rs]);
    }
    void update(int l,int r,int p,int x){
        if(l==r)return a[l]^=1,void();
        if(x<=mid)update(l,mid,ls,x);
        else update(mid+1,r,rs,x);
        tr[p]=merge(tr[ls],tr[rs]);
    }
}
using Segment_Tree::update;
using Segment_Tree::build;
using Segment_Tree::tr;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int q;cin>>n>>q;
    build(1,n,1);
    while(q--){
        int x;cin>>x,update(1,n,1,x);
        cout<<tr[1].mx<<"\n";
    }
}