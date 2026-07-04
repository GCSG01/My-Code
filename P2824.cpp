#include<bits/stdc++.h>
#define int long long
const int N=1e5+5;
using namespace std;
int n,m,K;
int a[N],b[N],c[N];
struct node{
    int op,l,r;
}qu[N];
int tr[N<<2];
int tag[N<<2];
#define ls p<<1
#define rs p<<1|1
void build(int l,int r,int p){
    tag[p]=-1;
    if(l==r)
        return tr[p]=c[l],void();
    int mid=(l+r)>>1;
    build(l,mid,ls);
    build(mid+1,r,rs);
    tr[p]=tr[ls]+tr[rs];
    return ;
}
void push_down(int p,int l,int r){
    if(tag[p]==-1)return ;
    tag[ls]=tag[rs]=tag[p];
    int mid=(l+r)>>1;
    if(!tag[p])tr[ls]=tr[rs]=0;
    else tr[ls]=(mid-l+1),tr[rs]=(r-mid);
    tag[p]=-1;
    return ;
}
void update(int l,int r,int p,int ql,int qr,int k){
    if(ql>qr)return ;
    if(ql<=l&&r<=qr)
        return tr[p]=(r-l+1)*k,tag[p]=k,void();
    int mid=(l+r)>>1;
    push_down(p,l,r);
    if(ql<=mid)update(l,mid,ls,ql,qr,k);
    if(qr>mid)update(mid+1,r,rs,ql,qr,k);
    tr[p]=tr[ls]+tr[rs];
    return ;
}
int query(int l,int r,int p,int ql,int qr){
    if(ql>qr)return 0;
    if(ql<=l&&r<=qr)return tr[p];
    int mid=(l+r)>>1,s=0;
    push_down(p,l,r);
    if(ql<=mid)s+=query(l,mid,ls,ql,qr);
    if(qr>mid)s+=query(mid+1,r,rs,ql,qr);
    return s;
}
#undef ls
#undef rs
int check(int x){
    for(int i=1;i<=n;i++)
        c[i]=(a[i]>=x);
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int l=qu[i].l,r=qu[i].r;
        int sum=query(1,n,1,l,r);
        if(!qu[i].op){
            update(1,n,1,l,r-sum,0);
            update(1,n,1,r-sum+1,r,1);
        }
        else{
            update(1,n,1,l,l+sum-1,1);
            update(1,n,1,l+sum,r,0);
        }
    }
    return query(1,n,1,K,K);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
    for(int i=1;i<=m;i++)cin>>qu[i].op>>qu[i].l>>qu[i].r;
    cin>>K;
    sort(b+1,b+n+1);
    int l=1,r=n,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(b[mid]))l=mid+1,ans=b[mid];
        else r=mid-1;
    }
    cout<<ans;
    return 0;
}
/*
1 2 6 5 4 3
1 2 5 6 4 3

0 0 1 1 0 0
0 0 1 1 0 0
0 0 1 1 0 0
*/