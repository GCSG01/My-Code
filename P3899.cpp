#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
vector<int>a[N];
int dfn[N],dft,deep[N],siz[N];
int ans[N];
int n,q;
struct node{
    int y,op,id;
};
vector<node>qu[N];
vector<int>Ad[N];
void dfs(int x,int ffa){
    dfn[x]=++dft,deep[x]=deep[ffa]+1,siz[x]=1;
    for(int y:a[x])
        if(y!=ffa)
            dfs(y,x),siz[x]+=siz[y];
    return ;
}
void add(int x,int y,int id){
    qu[x].push_back({y,1,id});
}
void del(int x,int y,int id){
    qu[x].push_back({y,-1,id});
}
void Update(int x1,int y1,int x2,int y2,int id){
    add(x2,y2,id);
    del(x1-1,y2,id);
    del(x2,y1-1,id);
    add(x1-1,y1-1,id);
    return ;
}
int tr[N];
inline int lowbit(int x){
    return x&-x;
}
void update(int x,int k){
    while(x<=n)
        tr[x]+=k,x+=lowbit(x);
    return ;
}
int query(int x,int s=0){
    while(x)
        s+=tr[x],x-=lowbit(x);
    return s;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>q;
    for(int i=1,u,v;i<n;i++)
        cin>>u>>v,a[u].push_back(v),a[v].push_back(u);
    dfs(1,0);
    for(int i=1;i<=q;i++){
        int p,k;cin>>p>>k;
        ans[i]+=min(deep[p]-1,k)*(siz[p]-1);
        Update(deep[p]+1,dfn[p]+1,min(n,deep[p]+k),dfn[p]+siz[p]-1,i);
    }
    for(int i=1;i<=n;i++)
        Ad[deep[i]].push_back(i);
    for(int i=1;i<=n;i++){
        for(int j:Ad[i])update(dfn[j],siz[j]-1);
        for(node j:qu[i])
            ans[j.id]+=query(j.y)*j.op;
    }
    for(int i=1;i<=q;i++)
        cout<<ans[i]<<"\n";
    return 0;
}