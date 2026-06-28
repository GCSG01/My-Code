#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e4+5;
vector<int>e[N];
int b[N],vis[N];
int n;
int fa[N][22],deep[N];
struct node{
    int l,r;
}a[N],tr[N];
void dfs(int x,int ffa){
    fa[x][0]=ffa,deep[x]=deep[ffa]+1;
    for(int i=1;i<=20;i++)fa[x][i]=fa[fa[x][i-1]][i-1];
    for(int y:e[x])
        if(y!=ffa)
            dfs(y,x);
    return ;
}
int lca(int x,int y){
    if(deep[x]<deep[y])swap(x,y);
    for(int i=20;i>=0;i--)
        if(deep[fa[x][i]]>=deep[y])
            x=fa[x][i];
    if(x==y)return x;
    for(int i=20;i>=0;i--)
        if(fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
int find(int x){
    return b[x]==x?x:b[x]=find(b[x]);
}
int dis(int x,int y){
    return deep[x]+deep[y]-2*deep[lca(x,y)]+1;
}
int merge(int x,int y){
    int fx=find(x),fy=find(y);b[fx]=fy;
    int l1=tr[fx].l,r1=tr[fx].r,l2=tr[fy].l,r2=tr[fy].r;
    int l=0,r=0,s=0;
    auto upd=[&](int a,int b){
        int d=dis(a,b);
        if(d>s)s=d,l=a,r=b;
    };
    upd(l1,r1);
    upd(l1,l2);
    upd(l1,r2);
    upd(r1,l2);
    upd(r1,r2);
    upd(l2,r2);
    tr[fy]={l,r};
    return s;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i].l,a[i].r=i,tr[i]={i,i},b[i]=i;
    for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        e[u].push_back(v),e[v].push_back(u);
    }
    dfs(1,0);
    sort(a+1,a+n+1,[](node A,node B){
        return A.l>B.l;
    });
    int ans=0;
    for(int i=1;i<=n;i++){
        int x=a[i].r,len=0;vis[x]=1;
        for(int j:e[x])
            if(vis[j])
                len=max(len,merge(x,j));
        // cout<<x<<" "<<a[i].l<<" "<<len<<"\n";
        ans=max(ans,a[i].l*len);
    }
    cout<<ans;
    return 0;
}