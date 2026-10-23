#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int N=1e7+5;
int tot;
namespace Segment_Tree{
    struct node{
        int lson,rson,v,tag;
    }tr[N<<2];
    #define ls(p) tr[p].lson
    #define rs(p) tr[p].rson
    #define mid ((l+r)>>1)
    inline void upd(int l,int r,int p,int k){
        tr[p].v+=(r-l+1)*k,tr[p].tag+=k;
    }
    inline void push_down(int l,int r,int p){
        if(!tr[p].tag)return ;
        if(!ls(p))ls(p)=++tot;
        if(!rs(p))rs(p)=++tot;
        upd(l,mid,ls(p),tr[p].tag),upd(mid+1,r,rs(p),tr[p].tag),tr[p].tag=0;
    }
    void push_up(int p){
        tr[p].v=tr[ls(p)].v+tr[rs(p)].v;
    }
    void update(int l,int r,int &p,int ql,int qr,int k){
        if(!p)p=++tot;
        if(ql<=l&&r<=qr)
            return upd(l,r,p,k);
        push_down(l,r,p);
        if(ql<=mid)update(l,mid,ls(p),ql,qr,k);
        if(qr>mid)update(mid+1,r,rs(p),ql,qr,k);
        push_up(p);
    }
    int query(int l,int r,int p,int ql,int qr){
        if(!p)return 0;
        if(ql<=l&&r<=qr)
            return tr[p].v;
        int sum=0;push_down(l,r,p);
        if(ql<=mid)sum+=query(l,mid,ls(p),ql,qr);
        if(qr>mid)sum+=query(mid+1,r,rs(p),ql,qr);
        return sum;
    }
}
using Segment_Tree::update;
using Segment_Tree::query;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n,m;cin>>n>>m;
    int rt=++tot;
    while(m--){
        int op,l,r,k;cin>>op>>l>>r;
        if(op==1)
            cin>>k,update(1,n,rt,l,r,k);
        else cout<<query(1,n,1,l,r)+(r+1)*r/2-(l-1)*l/2<<"\n";
    }
}