#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
const int N=1e5+5,inf=1e14+7;
int T,q;
int a[N];
#define ls p<<1
#define rs p<<1|1
struct Tag{
    int as,ad,has,had;
    Tag operator+(const Tag &B)const{
        Tag res;
        if(as==-inf){
            if(B.as==-inf){
                res.ad=ad+B.ad;
                res.as=-inf;
                res.had=max(had,ad+B.had);
                res.has=-inf;
            }
            else{
                res.ad=0;
                res.as=B.as;
                res.had=max(had,ad+B.had);
                res.has=B.has;
            }
        }
        else{
            if(B.as==-inf){
                res.ad=0;
                res.as=as+B.ad;
                res.had=had;
                res.has=max(has,as+B.had);
            }
            else{
                res.ad=0;
                res.as=B.as;
                res.had=had;
                res.has=max(has,max(as+B.had,B.has));
            }
        }
        return res;
    }
}tag[N<<2];
struct node{
    int as,has;
    node operator+(const node &B)const{
        return {max(as,B.as),max(has,B.has)};
    }
    node operator+(const Tag &B)const{
        return {B.as==-inf?as+B.ad:B.as,max({has,as+B.had,B.has})};
    }
}tr[N<<2];
void work(int p,Tag k){
    tr[p]=tr[p]+k;
    tag[p]=tag[p]+k;
    return ;
}
void push_down(int p){
    work(ls,tag[p]);
    work(rs,tag[p]);
    tag[p]={-inf,0,-inf,0};
    return ;
}
void build(int l,int r,int p){
    if(l==r)return tr[p]={a[l],a[l]},void();
    int mid=(l+r)>>1;
    build(l,mid,ls);
    build(mid+1,r,rs);
    tr[p]=tr[ls]+tr[rs];
    tag[p]={-inf,0,-inf,0};
    return ;
}
void update(int l,int r,int p,int ql,int qr,Tag k){
    if(ql<=l&&r<=qr)return work(p,k);
    int mid=(l+r)>>1;
    push_down(p);
    if(ql<=mid)update(l,mid,ls,ql,qr,k);
    if(qr>mid)update(mid+1,r,rs,ql,qr,k);
    tr[p]=tr[ls]+tr[rs];
    return ;
}
node query(int l,int r,int p,int ql,int qr){
    if(ql<=l&&r<=qr)return tr[p];
    node res={-inf,-inf};
    push_down(p);
    int mid=(l+r)>>1;
    if(ql<=mid)res=res+query(l,mid,ls,ql,qr);
    if(qr>mid)res=res+query(mid+1,r,rs,ql,qr);
    return res;
}
#undef ls
#undef rs
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>T;
    for(int i=1;i<=T;i++)cin>>a[i];
    build(1,T,1);
    cin>>q;
    while(q--){
        char op;int l,r,x;
        cin>>op>>l>>r;
        if(op=='Q')
            cout<<query(1,T,1,l,r).as<<"\n";
        else if(op=='A')
            cout<<query(1,T,1,l,r).has<<"\n";
        else if(op=='P')
            cin>>x,update(1,T,1,l,r,{-inf,x,-inf,x});
        else cin>>x,update(1,T,1,l,r,{x,0,x,0});
    }
    return 0;
}