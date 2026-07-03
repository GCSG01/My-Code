#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,m;
int p[N],a[N],b[N];
vector<int>e[N];
int rt[N],tot;
struct node{
    int l,r,v;
    node(){l=r=v=0;}
}tr[N*20];
int fa[N][30],dep[N];
#define ls(A) tr[(A)].l
#define rs(A) tr[(A)].r
int ins(int x,int l,int r,int v){
    int p=++tot;tr[p]=tr[x];
    if(l==r)return tr[p].v++,p;
    int mid=(l+r)>>1;
    if(v<=mid)ls(p)=ins(ls(p),l,mid,v);
    else rs(p)=ins(rs(p),mid+1,r,v);
    tr[p].v=tr[ls(p)].v+tr[rs(p)].v;
    return p;
}
int query(int u,int v,int ffa,int gfa,int l,int r,int k){
    if(l==r)return l;
    int mid=(l+r)>>1,sum=tr[ls(u)].v+tr[ls(v)].v-tr[ls(ffa)].v-tr[ls(gfa)].v;
    if(k<=sum)return query(ls(u),ls(v),ls(ffa),ls(gfa),l,mid,k);
    else return query(rs(u),rs(v),rs(ffa),rs(gfa),mid+1,r,k-sum);
}
void init(int x,int ffa){
    fa[x][0]=ffa,dep[x]=dep[ffa]+1;
    for(int i=1;i<=29;i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    rt[x]=ins(rt[ffa],1,n,a[x]);
    for(int y:e[x])
        if(y!=ffa)
            init(y,x);
    return ;
}
int LCA(int x,int y){
    if(x==y)return x;
    if(dep[x]<dep[y])swap(x,y);
    for(int i=29;i>=0;i--)
        if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
    if(x==y)return x;
    for(int i=29;i>=0;i--)
        if(fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>p[i],b[i]=p[i];
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++)
        a[i]=lower_bound(b+1,b+n+1,p[i])-b;
    for(int i=1;i<=n;i++)
        b[a[i]]=p[i];
    rt[0]=0;
    for(int i=1,u,v;i<n;i++)
        cin>>u>>v,e[u].push_back(v),e[v].push_back(u);
    init(1,0);
    int last=0;
    while(m--){
        int u,v,k;cin>>u>>v>>k,u^=last;
        int lca=LCA(u,v);
        cout<<(last=b[query(rt[u],rt[v],rt[lca],rt[fa[lca][0]],1,n,k)])<<"\n";
    }
    return 0;
}