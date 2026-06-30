#include<bits/stdc++.h>
using namespace std;
const int N=5e7+5;
int n,m;
struct node{
    int v,ls,rs;
}tr[N];
int rt[N],tot;
#define ls(A) tr[(A)].ls
#define rs(A) tr[(A)].rs
int nw(node x){
    return tr[++tot]=x,tot;
}
void build(int &p,int l,int r){
    p=++tot;
    if(l==r)return cin>>tr[p].v,void();
    int mid=(l+r)>>1;
    build(ls(p),l,mid),build(rs(p),mid+1,r);
    return ;
}
void insert(int v,int &p,int l,int r,int pos,int x){
    p=nw(tr[v]);
    if(l==r)return tr[p].v=x,void();
    int mid=(l+r)>>1;
    if(pos<=mid)insert(ls(p),ls(p),l,mid,pos,x);
    else insert(rs(p),rs(p),mid+1,r,pos,x);
    return ;
}
int query(int p,int l,int r,int pos){
    if(l==r)return tr[p].v;
    int mid=(l+r)>>1;
    if(pos<=mid)return query(ls(p),l,mid,pos);
    else return query(rs(p),mid+1,r,pos);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    build(rt[0],1,n);
    for(int i=1;i<=m;i++){
        int op,v,pos,x;cin>>v>>op>>pos;
        if(op==1)
            cin>>x,insert(rt[v],rt[i],1,n,pos,x);
        else cout<<query(rt[v],1,n,pos)<<"\n",rt[i]=rt[v];
    }
    return 0;
}