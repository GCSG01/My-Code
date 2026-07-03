#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int rt[N],vtot;
int n,tot;
struct node{
    int ls,rs,val,pri,siz,tag,sum;
}tr[N<<7];
#define ls(A) tr[(A)].ls
#define rs(A) tr[(A)].rs
int nw(int v){
    tot++,tr[tot].siz=1,ls(tot)=rs(tot)=0;
    tr[tot].val=v,tr[tot].sum=v,tr[tot].pri=rand();
    tr[tot].tag=0;
    return tot;
}
int clone(int p){
    int q=nw(0);tr[q]=tr[p];
    return q;
}
void update(int p){
    tr[p].siz=tr[ls(p)].siz+tr[rs(p)].siz+1;
    tr[p].sum=tr[ls(p)].sum+tr[rs(p)].sum+tr[p].val;
    return ;
}
void push_down(int p){
    if(!tr[p].tag)return ;
    if(ls(p))ls(p)=clone(ls(p));
    if(rs(p))rs(p)=clone(rs(p));
    swap(ls(p),rs(p));
    tr[ls(p)].tag^=1,tr[rs(p)].tag^=1,tr[p].tag=0;
    return ;
}
void split(int p,int x,int &l,int &r){
    if(!p)return l=r=0,void();
    push_down(p);
    if(tr[ls(p)].siz+1<=x)
        l=clone(p),split(rs(l),x-tr[ls(p)].siz-1,rs(l),r),update(l);
    else r=clone(p),split(ls(r),x,l,ls(r)),update(r);
    return ;
}
int merge(int l,int r){
    if(!l||!r)return l+r;
    push_down(l),push_down(r);
    if(tr[l].pri>tr[r].pri)
        return rs(l)=merge(rs(l),r),update(l),l;
    else return ls(r)=merge(l,ls(r)),update(r),r;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    srand(time(0));
    cin>>n;
    int lst=0;
    while(n--){
        int v,op,x,y,l,r,p;cin>>v>>op;
        if(op==1){
            cin>>x>>y,x^=lst,y^=lst;
            split(rt[v],x,l,p);
            rt[++vtot]=merge(merge(l,nw(y)),p);
        }
        else if(op==2){
            cin>>x,x^=lst;
            split(rt[v],x,l,r),split(l,x-1,l,p);
            rt[++vtot]=merge(l,r);
        }
        else if(op==3){
            cin>>x>>y,x^=lst,y^=lst;
            split(rt[v],y,l,r),split(l,x-1,l,p);
            tr[p].tag^=1,rt[++vtot]=merge(merge(l,p),r);
        }
        else{
            cin>>x>>y,x^=lst,y^=lst;
            split(rt[v],y,l,r),split(l,x-1,l,p);
            cout<<(lst=tr[p].sum)<<"\n";
            rt[++vtot]=merge(merge(l,p),r);
        }
    }
    return 0;
}