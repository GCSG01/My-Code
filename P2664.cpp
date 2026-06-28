#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
vector<int>a[N];
int c[N];
int siz[N],son[N];
int vis[N];
int cnt[N],ans[N],col[N],sum;
int n;
int root=0,rts;
void get_root(int x,int ffa){
    siz[x]=1,son[x]=0;
    for(int y:a[x])
        if(y!=ffa&&!vis[y]){
            get_root(y,x);
            siz[x]+=siz[y];
            son[x]=max(son[x],siz[y]);
        }
    son[x]=max(son[x],rts-siz[x]);
    if(son[x]<son[root])root=x;
    return ;
}
void update(int x,int fa,int v){
    cnt[c[x]]++;
    if(cnt[c[x]]==1)sum+=siz[x]*v,col[c[x]]+=siz[x]*v;
    for(int y:a[x])
        if(y!=fa&&!vis[y])
            update(y,x,v);
    cnt[c[x]]--;
}
void dfs1(int x,int fa){
    cnt[c[x]]++,siz[x]=1;
    for(int y:a[x])
        if(!vis[y]&&y!=fa){
            dfs1(y,x);
            siz[x]+=siz[y];
        }
    if(cnt[c[x]]==1)sum+=siz[x],col[c[x]]+=siz[x];
    cnt[c[x]]--;
    return ;
}
int sm=0;
void dfs2(int x,int fa,int kv){
    if(!cnt[c[x]])sum-=col[c[x]],sm++;
    cnt[c[x]]++;
    ans[x]+=sum+sm*kv;
    for(int y:a[x])
        if(y!=fa&&!vis[y])
            dfs2(y,x,kv);
    cnt[c[x]]--;
    if(!cnt[c[x]])sum+=col[c[x]],sm--;
    return ;
}
void clear(int x,int fa){
    cnt[c[x]]++;
    for(int y:a[x])
        if(!vis[y]&&y!=fa)
            clear(y,x);
    cnt[c[x]]--;
    if(!cnt[c[x]])sum-=siz[x],col[c[x]]-=siz[x];
    return ;
}
void calc(int x){
    dfs1(x,0),ans[x]+=sum;
    for(int y:a[x])
        if(!vis[y]){
            cnt[c[x]]++;
            sum-=siz[y],col[c[x]]-=siz[y];
            update(y,x,-1),cnt[c[x]]--;
            dfs2(y,x,siz[x]-siz[y]);
            cnt[c[x]]++,
            sum+=siz[y],col[c[x]]+=siz[y];
            update(y,x,1),cnt[c[x]]--;
        }
    return clear(x,0);
}
void work(int x){
    calc(x),vis[x]=1;
    for(int y:a[x])
        if(!vis[y]){
            root=0,rts=siz[y];
            get_root(y,0);
            work(root);
        }
    return ;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>c[i];
    for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        a[u].push_back(v),a[v].push_back(u);
    }
    son[0]=n+1,rts=n;
    get_root(1,0);
    work(root);
    for(int i=1;i<=n;i++)cout<<ans[i]<<"\n";
    return 0;
}