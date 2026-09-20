#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e4+5,G=61;
int n,q,p[N];
int fa[N][16],dep[N];
struct node{
    int a[G],p[G];
};
node bas[N];
vector<int>g[N];
inline void add(int u,int v){
    g[u].push_back(v),g[v].push_back(u);
}
void insert(node&a,int x,int id){
    for(int i=60;i>=0;i--){
        if(!((x>>i)&1))continue;
        if(!a.a[i])
            return a.a[i]=x,a.p[i]=id,void();
        if(dep[id]>dep[a.p[i]])
            swap(id,a.p[i]),swap(x,a.a[i]);
        x^=a.a[i];
    }
}
void merge(node &a,node b,int lca){
    for(int i=60;i>=0;i--)
        if(b.a[i]&&dep[b.p[i]]>=dep[lca])
            insert(a,b.a[i],b.p[i]);
}
void dfs(int x,int f){
    fa[x][0]=f,dep[x]=dep[f]+1,bas[x]=bas[f],insert(bas[x],p[x],x);
    for(int i=1;i<=14;i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    for(int y:g[x])
        if(y!=f)
            dfs(y,x);
}
int LCA(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    for(int i=14;i>=0;i--)
        if(dep[fa[x][i]]>=dep[y])
            x=fa[x][i];
    if(x==y)return x;
    for(int i=14;i>=0;i--)
        if(fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
int query(node a){
    int sum=0;
    for(int i=60;i>=0;i--)
        if(a.a[i]&&(sum^a.a[i])>sum)
            sum^=a.a[i];
    return sum;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>p[i];
    for(int i=1,u,v;i<n;i++)
        cin>>u>>v,add(u,v);
    dfs(1,0);
    while(q--){
        int u,v;cin>>u>>v;
        int lca=LCA(u,v);
        node ans={};
        merge(ans,bas[u],lca),merge(ans,bas[v],lca);
        cout<<query(ans)<<"\n";
    }
}