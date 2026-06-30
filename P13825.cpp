#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int N=2e6+5;
struct node{
    int v,tag,ls,rs;
}tr[N<<2];
int n,m,ToT;
#define ls tr[p].ls
#define rs tr[p].rs
void push_down(int p,int l,int r){
    if(!tr[p].tag)return ;
    int tp=tr[p].tag,mid=(l+r)>>1;tr[p].tag=0;
    if(!ls)ls=++ToT;
    if(!rs)rs=++ToT;
    tr[ls].tag+=tp,tr[rs].tag+=tp;
    tr[ls].v+=(mid-l+1)*tp,tr[rs].v+=(r-mid)*tp;
    return ;
}
void update(int &p,int l,int r,int s,int t,int k){
    if(!p)p=++ToT;
    if(s<=l&&r<=t)return tr[p].v+=(r-l+1)*k,tr[p].tag+=k,void();
    int mid=(l+r)>>1;
    push_down(p,l,r);
    if(s<=mid)update(ls,l,mid,s,t,k);
    if(t>mid)update(rs,mid+1,r,s,t,k);
    tr[p].v=tr[ls].v+tr[rs].v;
    return ;
}
int query(int p,int l,int r,int s,int t){
    if(s<=l&&r<=t)return tr[p].v;
    int mid=(l+r)>>1,sum=0;
    push_down(p,l,r);
    if(s<=mid)sum+=query(ls,l,mid,s,t);
    if(t>mid)sum+=query(rs,mid+1,r,s,t);
    return sum;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    int root=++ToT;
    while(m--){
        int op,l,r,x;cin>>op>>l>>r;
        if(op==1)
            cin>>x,update(root,1,n,l,r,x);
        else cout<<query(1,1,n,l,r)+r*(r+1)/2-l*(l-1)/2<<"\n";
    }
    return 0;
}