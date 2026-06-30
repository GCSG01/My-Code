#include<bits/stdc++.h>
using namespace std;
const int N=1e7+5;
int a[N],b[N];
int rt[N],tot;
struct node{
    int v,l,r;
}tr[N];
int n,m;
#define ls tr[p].l
#define rs tr[p].r
void build(int &p,int l,int r){
    p=++tot;
    if(l==r)return ;
    int mid=(l+r)>>1;
    build(ls,l,mid),build(rs,mid+1,r);
    return ;
}
void insert(int x,int &p,int l,int r,int v){
    p=++tot,tr[p]=tr[x];
    if(l==r)return tr[p].v++,void();
    int mid=(l+r)>>1;
    if(v<=mid)insert(tr[x].l,ls,l,mid,v);
    else insert(tr[x].r,rs,mid+1,r,v);
    tr[p].v=tr[ls].v+tr[rs].v;
    return ;
}
int query(int x,int y,int l,int r,int k){
    if(l==r)return l;
    int mid=(l+r)>>1,s=tr[tr[y].l].v-tr[tr[x].l].v;
    if(k<=s)return query(tr[x].l,tr[y].l,l,mid,k);
    else return query(tr[x].r,tr[y].r,mid+1,r,k-s);
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
    sort(b+1,b+n+1);
    int nn=unique(b+1,b+n+1)-b-1;
    build(rt[0],1,nn);
    for(int i=1;i<=n;i++)
        a[i]=lower_bound(b+1,b+nn+1,a[i])-b,
        insert(rt[i-1],rt[i],1,nn,a[i]);
    // for(int i=1;i<=n;i++)cout<<rt[i]<<" ";
    while(m--){
        int l,r,k;cin>>l>>r>>k;
        cout<<b[query(rt[l-1],rt[r],1,nn,k)]<<"\n";
    }
    return 0;
}