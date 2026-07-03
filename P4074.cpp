#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m,q;
int v[N],w[N];
vector<int>e[N];
int fa[N][31],dfn[N],dep[N],idx;
int in[N],out[N],vis[N];
int c[N];
int flag[N],cnt[N];
int ans[N],sum;
struct CG{
    int pos,candy;
}cg[N];
struct QU{
    int lca,id,t,x,y,l,r;
}qu[N];
int sc,sq,bk;
void dfs(int x,int ffa){
    in[x]=++idx,dfn[idx]=x;
    for(auto y:e[x])
        if(y!=ffa)dfs(y,x);
    out[x]=++idx,dfn[idx]=x;
    return ;
}
void dfs2(int x,int ffa){
    vis[x]=1,fa[x][0]=ffa,dep[x]=dep[ffa]+1;
    for(int i=1;i<=29;i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    for(auto y:e[x])
        if(!vis[y])dfs2(y,x);
    return ;
}
int LCA(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    for(int i=29;i>=0;i--)
        if(dep[fa[x][i]]>=dep[y])
            x=fa[x][i];
    if(x==y)return x;
    for(int i=29;i>=0;i--)
        if(fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
void update(int pos,int val){
    if(flag[pos]==1){
        sum-=w[cnt[c[pos]]]*v[c[pos]];
        cnt[c[pos]]--;
    }
    flag[pos]+=val;
    if(flag[pos]==1){
        cnt[c[pos]]++;
        sum+=w[cnt[c[pos]]]*v[c[pos]];
    }
    return ;
}
void update_t(int idx){
    int pos=cg[idx].pos;
    sum-=w[cnt[c[pos]]]*v[c[pos]];
    cnt[c[pos]]--;
    if(flag[pos]==1)swap(c[pos],cg[idx].candy);
    cnt[c[pos]]++;
    sum+=w[cnt[c[pos]]]*v[c[pos]];
    if(flag[pos]!=1)swap(c[pos],cg[idx].candy);
    return ;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>q;
    for(int i=1;i<=m;i++)cin>>v[i];
    for(int i=1;i<=n;i++)cin>>w[i];
    for(int i=1,u,vv;i<n;i++)
        cin>>u>>vv,e[u].push_back(vv),
        e[vv].push_back(u);
    for(int i=1;i<=n;i++)cin>>c[i];
    dfs(1,0);
    memset(vis,0,sizeof(vis));
    dep[0]=-1;
    dfs2(1,0);
    bk=pow(n*2,1.00/2);    
    for(int i=1;i<=q;i++){
        int op,x,y;cin>>op>>x>>y;
        if(!op)
            cg[++sc]={x,y};
        else{
            if(in[x]>in[y])swap(x,y);
            int lca=LCA(x,y);
            qu[++sq]={lca,sq,sc,x,y,0,0};
            if(qu[sq].lca==qu[sq].x){
                qu[sq].l=in[qu[sq].x];
                qu[sq].r=in[qu[sq].y];
                qu[sq].lca=0;
            }
            else{
                qu[sq].l=out[qu[sq].x];
                qu[sq].r=in[qu[sq].y];
            }
        }
    }
    sort(qu+1,qu+sq+1,[](QU A,QU B){
        return A.l/bk==B.l/bk?(A.r/bk==B.r/bk?A.t<B.t:A.r<B.r):A.l/bk<B.l/bk;
    });
    int l=1,r=0,t=0;
    for(int i=1;i<=sq;i++){
        while(t<qu[i].t)update_t(++t);
        while(t>qu[i].t)update_t(t--);
        while(r<qu[i].r)update(dfn[++r],1);
        while(r>qu[i].r)update(dfn[r--],-1);
        while(l<qu[i].l)update(dfn[l++],-1);
        while(l>qu[i].l)update(dfn[--l],1);
        if(qu[i].lca)
            cnt[c[qu[i].lca]]++,sum+=w[cnt[c[qu[i].lca]]]*v[c[qu[i].lca]];
        ans[qu[i].id]=sum;
        if(qu[i].lca)
            cnt[c[qu[i].lca]]--,sum-=w[cnt[c[qu[i].lca]]+1]*v[c[qu[i].lca]];
    }
    for(int i=1;i<=sq;i++)
        cout<<ans[i]<<"\n";
    return 0;
}