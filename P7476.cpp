#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m;
int mx[N<<4];
priority_queue<int>tr[N<<4];
#define ls p<<1
#define rs p<<1|1
void push_up(int p){
    mx[p]=max(mx[ls],mx[rs]);
    if(!tr[p].empty())mx[p]=max(mx[p],tr[p].top());
    return ;
}
void update(int l,int r,int p,int ll,int rr,int k){
    if(ll<=l&&r<=rr)return tr[p].push(k),mx[p]=max(mx[p],k),void();
    int mid=(l+r)>>1;
    if(ll<=mid)update(l,mid,ls,ll,rr,k);
    if(rr>mid)update(mid+1,r,rs,ll,rr,k);
    push_up(p);
    return ;
}
void push_down(int l,int r,int p,int ll,int rr,int k){
    if(ll<=l&&r<=rr)return ;
    int mid=(l+r)>>1;
    if(rr<=mid)tr[rs].push(k),mx[rs]=max(mx[rs],k),push_down(l,mid,ls,ll,rr,k);
    else if(ll>mid)tr[ls].push(k),mx[ls]=max(mx[ls],k),push_down(mid+1,r,rs,ll,rr,k);
    else push_down(l,mid,ls,ll,rr,k),push_down(mid+1,r,rs,ll,rr,k);
    return push_up(p);
}
void del(int l,int r,int p,int ll,int rr,int k){
    if(ll<=l&&r<=rr&&mx[p]<k)return ;
    if(!tr[p].empty()&&tr[p].top()==k)
        return tr[p].pop(),push_down(l,r,p,ll,rr,k),push_up(p);
    int mid=(l+r)>>1;
    if(ll<=mid)del(l,mid,ls,ll,rr,k);
    if(rr>mid)del(mid+1,r,rs,ll,rr,k);
    return push_up(p);
}
int query(int l,int r,int p,int ll,int rr){
    if(ll<=l&&r<=rr)return mx[p];
    int mid=(l+r)>>1,mx=-1;
    if(!tr[p].empty())mx=tr[p].top();
    if(ll<=mid)mx=max(mx,query(l,mid,ls,ll,rr));
    if(rr>mid)mx=max(mx,query(mid+1,r,rs,ll,rr));
    return mx;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    memset(mx,-1,sizeof mx);
    while(m--){
        int op,l,r,k;cin>>op>>l>>r;
        if(op==1)
            cin>>k,update(1,n,1,l,r,k);
        else if(op==2){
            k=query(1,n,1,l,r);
            if(k!=-1)del(1,n,1,l,r,k);
        }
        else cout<<query(1,n,1,l,r)<<"\n";
    }
    return 0;
}