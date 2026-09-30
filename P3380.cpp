#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+5;
inline int lowbit(int x){
    return x&-x;
}
struct Tree{
    struct node{
        int v,ls,rs;
    }tr[N*100];
    int tot;
    Tree(){
        memset(tr,0,sizeof tr);
        tot=0;
    }
    #define ls tr[p].ls
    #define rs tr[p].rs
    void push_up(int p){
        tr[p].v=tr[ls].v+tr[rs].v;
        return ;
    }
    void update(int &p,int l,int r,int k,int v){
        if(!p)p=++tot;
        if(l==r)return tr[p].v+=v,void();
        int mid=(l+r)>>1;
        if(k<=mid)update(ls,l,mid,k,v);
        else update(rs,mid+1,r,k,v);
        push_up(p);
        return ;
    }
    #undef ls
    #undef rs
}tre;
struct BIT{
    int n,len;
    int tr[N];
    BIT(int nn,int lenn):n(nn),len(lenn){
        memset(tr,0,sizeof tr);
    }
    void add(int pos,int v,int a[]){
        for(int i=pos;i<=n;i+=lowbit(i))
            tre.update(tr[i],1,len,a[pos],v);
    }
};
int n,m,len;
int a[N],b[N];
struct node{
    int a,b,c,d;
}q[N];
BIT *bit;
int tm1[N],tm2[N],cnt,cnt2;
int query_rnk(int l,int r,int k){
    if(l==r)return l;
    int mid=(l+r)>>1,s=0;
    for(int i=1;i<=cnt;i++)s+=tre.tr[tre.tr[tm1[i]].ls].v;
    for(int i=1;i<=cnt2;i++)s-=tre.tr[tre.tr[tm2[i]].ls].v;
    if(s>=k){
        for(int i=1;i<=cnt;i++)tm1[i]=tre.tr[tm1[i]].ls;
        for(int i=1;i<=cnt2;i++)tm2[i]=tre.tr[tm2[i]].ls;
        return query_rnk(l,mid,k);
    }
    else{
        for(int i=1;i<=cnt;i++)tm1[i]=tre.tr[tm1[i]].rs;
        for(int i=1;i<=cnt2;i++)tm2[i]=tre.tr[tm2[i]].rs;
        return query_rnk(mid+1,r,k-s);
    }
    return -1;
}
int Find_num(int l,int r,int k){
    cnt=cnt2=0;
    for(int i=r;i;i-=lowbit(i))tm1[++cnt]=bit->tr[i];
    for(int i=l-1;i;i-=lowbit(i))tm2[++cnt2]=bit->tr[i];
    return query_rnk(1,len,k);
}
int Query_rnk(int l,int r,int k){
    if(l==r)return 0;
    int mid=(l+r)>>1,s=0;
    if(k<=mid){
        for(int i=1;i<=cnt;i++)tm1[i]=tre.tr[tm1[i]].ls;
        for(int i=1;i<=cnt2;i++)tm2[i]=tre.tr[tm2[i]].ls;
        return Query_rnk(l,mid,k);
    }
    else{
        for(int i=1;i<=cnt;i++)s+=tre.tr[tre.tr[tm1[i]].ls].v,tm1[i]=tre.tr[tm1[i]].rs;
        for(int i=1;i<=cnt2;i++)s-=tre.tr[tre.tr[tm2[i]].ls].v,tm2[i]=tre.tr[tm2[i]].rs;
        return s+Query_rnk(mid+1,r,k);
    }
    return -1;
}
int Find_rnk(int l,int r,int k){
    cnt=cnt2=0;
    for(int i=r;i;i-=lowbit(i))tm1[++cnt]=bit->tr[i];
    for(int i=l-1;i;i-=lowbit(i))tm2[++cnt2]=bit->tr[i];
    return Query_rnk(1,len,k)+1;
}
int Find_pre(int l,int r,int k){
    int rk=Find_rnk(l,r,k)-1;
    if(!rk)return 0;
    return Find_num(l,r,rk);
}
int Find_nxt(int l,int r,int k){
    if(k==len)return len+1;
    int rk=Find_rnk(l,r,k+1);
    if(rk==r-l+2)return len+1;
    return Find_num(l,r,rk);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i],b[++len]=a[i];
    for(int i=1;i<=m;i++){
        int op,x,y,z=0;cin>>op>>x>>y;
        if(op!=3)cin>>z;
        if(op==3||op==1||op==4||op==5)b[++len]=op==3?y:z;
        q[i]={op,x,y,z};
    }
    sort(b+1,b+len+1);
    len=unique(b+1,b+len+1)-b-1;
    bit=new BIT(n,len);
    for(int i=1;i<=n;i++)
        a[i]=lower_bound(b+1,b+len+1,a[i])-b,bit->add(i,1,a);
    b[0]=-2147483647,b[len+1]=2147483647;
    for(int i=1;i<=m;i++){
        int op=q[i].a,x=q[i].b,y=q[i].c,z=q[i].d;
        if(op==1||op==4||op==5)z=lower_bound(b+1,b+len+1,z)-b;
        if(op==1)
            cout<<Find_rnk(x,y,z)<<"\n";
        else if(op==2)
            cout<<b[Find_num(x,y,z)]<<"\n";
        else if(op==3)
            bit->add(x,-1,a),a[x]=lower_bound(b+1,b+len+1,y)-b,
            bit->add(x,1,a);
        else if(op==4)
            cout<<b[Find_pre(x,y,z)]<<"\n";
        else cout<<b[Find_nxt(x,y,z)]<<"\n";
    }
    return 0;
}