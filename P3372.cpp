#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,m;
int tr[N<<2],tag[N<<2],s[N];
#define ls p<<1
#define rs p<<1|1
#define mid ((l+r)>>1)
void upd(int l,int r,int p,int k){
    tr[p]+=(r-l+1)*k,tag[p]+=k;
}
void push_down(int l,int r,int p){
    if(!tag[p])return ;
    upd(l,mid,ls,tag[p]),upd(mid+1,r,rs,tag[p]),tag[p]=0;
}
void push_up(int p){
    tr[p]=tr[ls]+tr[rs];
}
void update(int l,int r,int p,int s,int t,int k){
    if(s<=l&&r<=t)return upd(l,r,p,k);
    push_down(l,r,p);
    if(s<=mid)update(l,mid,ls,s,t,k);
    if(t>mid)update(mid+1,r,rs,s,t,k);
    push_up(p);
}
int query(int l,int r,int p,int s,int t){
    if(s<=l&&r<=t)return tr[p];
    int sum=0;
    push_down(l,r,p);
    if(s<=mid)sum+=query(l,mid,ls,s,t);
    if(t>mid)sum+=query(mid+1,r,rs,s,t);
    return sum;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>s[i],s[i]+=s[i-1];
    while(m--){
        int op,l,r,x;cin>>op>>l>>r;
        if(op==1)
            cin>>x,update(1,n,1,l,r,x);
        else cout<<query(1,n,1,l,r)+s[r]-s[l-1]<<"\n";
    }
    return 0;
}