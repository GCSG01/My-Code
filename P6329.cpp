#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
vector<int>a[N];
int n,m;
int v[N],fa2[N];
int siz[N],son[N];
int vis[N],fa[N][20],deep[N];
struct BIT{
    vector<int>tr;
    int n;
    void build(int nn){
        n=nn,tr.resize(n+20);
    }
    inline int lowbit(int x){
        return x&-x;
    }
    void add(int x,int k){
        while(x<=n)tr[x]+=k,x+=lowbit(x);
    }
    int query(int x,int s=0){
        x=min(x,n);
        while(x)s+=tr[x],x-=lowbit(x);
        return s;
    }
}tr1[N],tr2[N];
void dfs1(int x,int ffa){
    fa[x][0]=ffa,deep[x]=deep[ffa]+1;
    for(int i=1;i<=19;i++)fa[x][i]=fa[fa[x][i-1]][i-1];
    for(int y:a[x])
        if(y!=ffa)dfs1(y,x);
    return ;
}
int lca(int x,int y){
    if(deep[x]<deep[y])swap(x,y);
    for(int i=19;i>=0;i--)
        if(deep[fa[x][i]]>=deep[y])
            x=fa[x][i];
    if(x==y)return x;
    for(int i=19;i>=0;i--)
        if(fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
int get_dis(int x,int y){
    return deep[x]+deep[y]-2*deep[lca(x,y)];
}
int qu[N],qtot;
void get_rt(int x,int ffa){
    qu[++qtot]=x,siz[x]=1;
    for(int y:a[x])
        if(!vis[y]&&y!=ffa)
            get_rt(y,x),siz[x]+=siz[y],son[x]=max(son[x],siz[y]);
    return ;
}
void dfs2(int rt,int x,int ffa,int k){
    tr1[rt].add(k,v[x]);
    for(int y:a[x])
        if(!vis[y]&&y!=ffa)
            dfs2(rt,y,x,k+1);
    return ;
}
void build_tree(int x,int ffa){
    qtot=0;
    get_rt(x,0);
    for(int i=1;i<=qtot;i++)
        son[qu[i]]=max(son[qu[i]],qtot-siz[qu[i]]);
    int rt=qu[1];
    for(int i=2;i<=qtot;i++)
        if(son[rt]>son[qu[i]])rt=qu[i];
    for(int i=1;i<=qtot;i++)son[qu[i]]=0;
    vis[rt]=1,fa2[rt]=ffa,x=rt;
    tr1[x].build(qtot);
    tr2[x].build(qtot);
    if(ffa)
        for(int i=1;i<=qtot;i++)
            tr2[x].add(get_dis(qu[i],ffa),v[qu[i]]);
    for(int y:a[x])
        if(!vis[y])
            dfs2(x,y,x,1);
    for(int y:a[x])
        if(!vis[y])
            build_tree(y,x);
    return ;
}
void update(int x,int k){
    int xx=x;
    while(fa2[xx]){
        int d=get_dis(fa2[xx],x);
        tr2[xx].add(d,-v[x]);
        tr2[xx].add(d,k);
        xx=fa2[xx];
        tr1[xx].add(d,-v[x]);
        tr1[xx].add(d,k);
    }
    v[x]=k;
    return ;
}
int query(int x,int k){
    int xx=x,ans=v[x]+tr1[x].query(k);
    while(fa2[xx]){
        int d=get_dis(fa2[xx],x);
        // cout<<x<<" "<<xx<<" "<<fa2[xx]<<" "<<v[fa2[xx]]<<" "<<tr1[fa2[xx]].query(k-d)<<" "<<tr2[xx].query(k-d)<<"\n";
        if(d<=k)ans+=v[fa2[xx]]+tr1[fa2[xx]].query(k-d)-tr2[xx].query(k-d);
        xx=fa2[xx];
    }
    // cout<<x<<" "<<ans<<"\n";
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>v[i];
    for(int i=1,u,v;i<n;i++)
        cin>>u>>v,a[u].push_back(v),a[v].push_back(u);
    dfs1(1,0);
    build_tree(1,0);
    int lstans=0;
    while(m--){
        int op,x,y,k;
        cin>>op>>x,x^=lstans;
        if(!op){
            cin>>k,k^=lstans;
            cout<<(lstans=query(x,k))<<"\n";
        }
        else cin>>y,y^=lstans,update(x,y);
    }
    return 0;
}