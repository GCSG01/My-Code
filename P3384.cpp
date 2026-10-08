#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int mod,n,m,rt,cnt;
vector<int>g[N];
int v[N],fa[N],dep[N],dfn[N],siz[N],son[N],top[N],dfnn[N];
namespace SegmentTree{
    struct node{
        int v,ls,rs,tag;
    }tr[N<<2];
    #define ls(p) tr[(p)].ls
    #define rs(p) tr[(p)].rs
    #define mid ((l+r)>>1)
    inline void push_up(int p){
        tr[p].v=(tr[ls(p)].v+tr[rs(p)].v)%mod;
    }
    void upd(int l,int r,int p,int tag){
        tr[p].tag+=tag,tr[p].tag%=mod,tr[p].v+=tag*(r-l+1)%mod,tr[p].v%=mod;
    }
    inline void push_down(int l,int r,int p){
        if(!tr[p].tag)return ;
        upd(l,mid,ls(p),tr[p].tag),upd(mid+1,r,rs(p),tr[p].tag),tr[p].tag=0;
    }
    void build(int l,int r,int p){
        if(l==r)return tr[p].v=v[dfnn[l]]%mod,void();
        tr[p].ls=++cnt,tr[p].rs=++cnt;
        build(l,mid,ls(p)),build(mid+1,r,rs(p));
        push_up(p);
    }
    void update(int l,int r,int p,int ql,int qr,int v){
        if(ql<=l&&r<=qr)return upd(l,r,p,v);
        push_down(l,r,p);
        if(ql<=mid)update(l,mid,ls(p),ql,qr,v);
        if(qr>mid)update(mid+1,r,rs(p),ql,qr,v);
        push_up(p);
    }
    int query(int l,int r,int p,int ql,int qr){
        if(ql<=l&&r<=qr)return tr[p].v;
        push_down(l,r,p);
        int sum=0;
        if(ql<=mid)sum+=query(l,mid,ls(p),ql,qr);
        if(qr>mid)sum+=query(mid+1,r,rs(p),ql,qr);
        return sum%mod;
    }
}
void dfs1(int x){
    siz[x]=1,dep[x]=dep[fa[x]]+1;
    for(int y:g[x])
        if(y!=fa[x]){
            fa[y]=x,dfs1(y),siz[x]+=siz[y];
            if(siz[son[x]]<siz[y])son[x]=y;
        }
}
void dfs2(int x,int tp){
    top[x]=tp,dfn[x]=++cnt,dfnn[cnt]=x;
    if(son[x])dfs2(son[x],tp);
    for(int y:g[x])
        if(y!=fa[x]&&y!=son[x])
            dfs2(y,y);
}
int query(int x,int y){
    int ans=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        ans=(ans+SegmentTree::query(1,n,1,dfn[top[x]],dfn[x]))%mod;
        x=fa[top[x]];
    }
    if(dfn[x]>dfn[y])swap(x,y);
    return (ans+SegmentTree::query(1,n,1,dfn[x],dfn[y]))%mod;
}
void update(int x,int y,int c){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        SegmentTree::update(1,n,1,dfn[top[x]],dfn[x],c);
        x=fa[top[x]];
    }
    if(dfn[x]>dfn[y])swap(x,y);
    SegmentTree::update(1,n,1,dfn[x],dfn[y],c);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>rt>>mod;
    for(int i=1;i<=n;i++)cin>>v[i];
    for(int i=1,u,v;i<n;i++)
        cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
    dfs1(rt),dfs2(rt,rt),cnt=1;
    SegmentTree::build(1,n,1);
    while(m--){
        int op,x,y,z;cin>>op;
        if(op==1)
            cin>>x>>y>>z,update(x,y,z);
        else if(op==2)
            cin>>x>>y,cout<<query(x,y)<<"\n";
        else if(op==3)
            cin>>x>>z,SegmentTree::update(1,n,1,dfn[x],dfn[x]+siz[x]-1,z);
        else cin>>x,cout<<SegmentTree::query(1,n,1,dfn[x],dfn[x]+siz[x]-1)<<"\n";
    }
}