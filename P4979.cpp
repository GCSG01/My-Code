#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,m,a[N];
struct node{
    int ans,x,tag;
}tr[N<<2];
#define ls p<<1
#define rs p<<1|1
#define mid ((l+r)>>1)
inline void push_up(int p){
    if(!tr[ls].x||!tr[rs].x||tr[ls].x!=tr[rs].x)tr[p].ans=1,tr[p].x=0;
    else tr[p].x=tr[ls].x;
}
inline void upd(int p,int k){
    tr[p].ans=0,tr[p].x=tr[p].tag=k;
}
inline void push_down(int p){
    if(!tr[p].tag)return ;
    upd(ls,tr[p].tag),upd(rs,tr[p].tag),tr[p].tag=0;
}
void build(int l,int r,int p){
    if(l==r)
        return tr[p].x=a[l],void();
    build(l,mid,ls),build(mid+1,r,rs),push_up(p);
}
void update(int l,int r,int p,int s,int t,int k){
    if(s<=l&&r<=t)
        return upd(p,k);
    push_down(p);
    if(s<=mid)update(l,mid,ls,s,t,k);
    if(t>mid)update(mid+1,r,rs,s,t,k);
    push_up(p);
}
node query(int l,int r,int p,int s,int t){
    if(s<=l&&r<=t)return tr[p];
    push_down(p);
    if(t<=mid)return query(l,mid,ls,s,t);
    if(s>mid)return query(mid+1,r,rs,s,t);
    node a=query(l,mid,ls,s,t);
    node b=query(mid+1,r,rs,s,t);
    node x={};
    if(!a.x||!b.x||a.x!=b.x)x.ans=1,x.x=0;
    else x.x=a.x;
    return x;
}
int rd(){
    char c;cin>>c;
    return c-'A'+1;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)a[i+1]=rd();
    n+=2,a[1]=-1,a[n]=4;
    cin>>m,build(1,n,1);
    while(m--){
        char op;
        int l,r,x;cin>>op>>l>>r,l++,r++;
        if(op=='A')
            x=rd(),update(1,n,1,l,r,x);
        else{
            node x=query(1,n,1,l,r);
            if(x.ans)cout<<"No\n";
            else if(query(1,n,1,l-1,l-1).x==query(1,n,1,r+1,r+1).x)
                cout<<"No\n";
            else cout<<"Yes\n";
        }
    }
}