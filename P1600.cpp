#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int n,m,w[N];
int fa[N][20],dep[N];
vector<int>g[N];
int rt[N][2];
int Ans[N];
namespace Segment_Tree{
    struct node{
        int ls,rs,cnt;
    }tr[N*40];
    int tot;
    #define ls(p) tr[p].ls
    #define rs(p) tr[p].rs
    #define mid ((l+r)>>1)
    void update(int l,int r,int &p,int x,int v){
        if(!p)p=++tot;
        tr[p].cnt+=v;
        if(l==r)return ;
        if(x<=mid)update(l,mid,ls(p),x,v);
        else update(mid+1,r,rs(p),x,v);
    }
    int query(int l,int r,int p,int x){
        if(!p||x<l||x>r)return 0;
        if(l==r)return tr[p].cnt;
        if(x<=mid)return query(l,mid,ls(p),x);
        else return query(mid+1,r,rs(p),x);
    }
    int merge(int x,int y,int l,int r){
        if(!x||!y)return x+y;
        if(l==r)return tr[x].cnt+=tr[y].cnt,x;
        ls(x)=merge(ls(x),ls(y),l,mid),
        rs(x)=merge(rs(x),rs(y),mid+1,r);
        tr[x].cnt=tr[ls(x)].cnt+tr[rs(x)].cnt;
        return x;
    }
}
using Segment_Tree::update;
using Segment_Tree::query;
using Segment_Tree::merge;
void dfs(int x,int ffa){
    fa[x][0]=ffa,dep[x]=dep[ffa]+1;
    for(int i=1;i<=17;i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    for(int y:g[x])
        if(y!=ffa)dfs(y,x);
}
int LCA(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    for(int i=17;i>=0;i--)
        if(dep[fa[x][i]]>=dep[y])
            x=fa[x][i];
    if(x==y)return x;
    for(int i=17;i>=0;i--)
        if(fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
void solve(int x){
    for(int y:g[x])
        if(y!=fa[x][0])
            solve(y),rt[x][0]=merge(rt[x][0],rt[y][0],1,n),
            rt[x][1]=merge(rt[x][1],rt[y][1],-n,2*n);
    Ans[x]=query(1,n,rt[x][0],dep[x]+w[x])+query(-n,2*n,rt[x][1],dep[x]-w[x]);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1,u,v;i<n;i++)
        cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
    for(int i=1;i<=n;i++)cin>>w[i];
    dfs(1,0);
    for(int i=1;i<=m;i++){
        int s,t;cin>>s>>t;
        int lca=LCA(s,t);
        update(1,n,rt[s][0],dep[s],1);
        update(1,n,rt[lca][0],dep[s],-1);
        int k=2*dep[lca]-dep[s];
        update(-n,2*n,rt[t][1],k,1);
        if(fa[lca][0])update(-n,2*n,rt[fa[lca][0]][1],k,-1);
    }
    solve(1);
    for(int i=1;i<=n;i++)cout<<Ans[i]<<" ";
}