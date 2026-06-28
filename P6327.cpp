#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
double si[N<<2],co[N<<2];
int tag[N<<2];
int a[N];
int n,m;
#define ls p<<1
#define rs p<<1|1
void push_up(int p){
    si[p]=si[ls]+si[rs];
    co[p]=co[ls]+co[rs];
    return ;
}
void add(int p,int v){
    double x=si[p],y=co[p];
    double sv=sin(v),cv=cos(v);
    si[p]=x*cv+y*sv,co[p]=y*cv-x*sv;
    tag[p]+=v;
    return ;
}
void push_down(int p){
    if(!tag[p])return ;
    add(ls,tag[p]),add(rs,tag[p]);
    tag[p]=0;
    return ;
}
void build(int l,int r,int p){
    if(l==r)return si[p]=sin(a[l]),co[p]=cos(a[l]),void();
    int mid=(l+r)>>1;
    build(l,mid,ls);
    build(mid+1,r,rs);
    push_up(p);
    return ;
}
void update(int l,int r,int p,int ll,int rr,int v){
    if(ll<=l&&r<=rr)return add(p,v);
    int mid=(l+r)>>1;
    push_down(p);
    if(ll<=mid)update(l,mid,ls,ll,rr,v);
    if(rr>mid)update(mid+1,r,rs,ll,rr,v);
    push_up(p);
    return ;
}
double query(int l,int r,int p,int ll,int rr){
    if(ll<=l&&r<=rr)return si[p];
    int mid=(l+r)>>1;
    double s=0;
    push_down(p);
    if(ll<=mid)s+=query(l,mid,ls,ll,rr);
    if(rr>mid)s+=query(mid+1,r,rs,ll,rr);
    return s;
}
#undef ls
#undef rs
signed main(){
    // ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    build(1,n,1);
    cin>>m;
    while(m--){
        int op,l,r,v;cin>>op>>l>>r;
        if(op==1)cin>>v,update(1,n,1,l,r,v);
        else printf("%.1f\n",query(1,n,1,l,r));
    }
    return 0;
}