#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
#ifdef ONLINE_JUDGE
    #define getchar getchar_unlocked
#endif
void rd(int &x){
    cin>>x;
    // char c=getchar();x=0;
    // while(c<'0'||c>'9')c=getchar();
    // while(c>='0'&&c<='9')
    //     x=x*10+c-'0',c=getchar();
}
struct node{
    int val,mul,add;
}tr[N<<2];
int n,P;
int a[N];
inline int ls(int p){return p<<1;}
inline int rs(int p){return p<<1|1;}
void apply(int p,int len,int km,int ka){
    km%=P,ka%=P;
    tr[p].val=(tr[p].val*km%P+ka*len%P)%P;
    tr[p].mul=tr[p].mul*km%P;
    tr[p].add=(tr[p].add*km%P+ka)%P;
    return ;
}
inline void push_up(int p){
    tr[p].val=(tr[ls(p)].val+tr[rs(p)].val)%P;
}
inline void push_down(int l,int r,int p){
    if(tr[p].mul==1&&!tr[p].add)
        return;
    int mid=(l+r)>>1;
    apply(ls(p),mid-l+1,tr[p].mul,tr[p].add);
    apply(rs(p),r-mid,tr[p].mul,tr[p].add);
    tr[p].mul=1,tr[p].add=0;
    return ;
}
void build(int l,int r,int p){
    tr[p]={0,1,0};
    if(l==r)
        return tr[p]={a[l]%P,1,0},void();
    int mid=(l+r)>>1;
    build(l,mid,ls(p));
    build(mid+1,r,rs(p));
    return push_up(p);
}
void update(int l,int r,int p,int s,int t,int km,int ka){
    if(s<=l&&r<=t)return apply(p,r-l+1,km,ka);;
    push_down(l,r,p);
    int mid=(l+r)>>1;
    if(s<=mid)update(l,mid,ls(p),s,t,km,ka);
    if(t>mid)update(mid+1,r,rs(p),s,t,km,ka);
    return push_up(p);
}
int query(int l,int r,int p,int s,int t){
    if(s<=l&&r<=t)return tr[p].val;
    push_down(l,r,p);
    int sum=0,mid=(l+r)>>1;
    if(s<=mid)sum+=query(l,mid,ls(p),s,t);
    if(t>mid)sum+=query(mid+1,r,rs(p),s,t);
    return sum%P;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    rd(n),rd(P);
    for(int i=1;i<=n;i++)rd(a[i]);
    build(1,n,1);
    int m;rd(m);
    while(m--){
        int op,l,r,x;rd(op),rd(l),rd(r);
        if(op==1)
            rd(x),update(1,n,1,l,r,x,0);
        else if(op==2)
            rd(x),update(1,n,1,l,r,1,x);
        else cout<<query(1,n,1,l,r)<<"\n";
    }
    return 0;
}