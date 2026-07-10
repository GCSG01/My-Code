#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,m,k;
int x[N],y[N];
int f[N],d[N];
struct node{
    int l,r;
    vector<int>e;
}tr[N<<2];
#define ls p<<1
#define rs p<<1|1
void build(int p,int l,int r){
    tr[p].l=l,tr[p].r=r;
    if(l==r)return ;
    int mid=(tr[p].l+tr[p].r)>>1;
    build(ls,l,mid),build(rs,mid+1,r);
    return ;
}
void insert(int p,int l,int r,int i){
    if(tr[p].l>=l&&tr[p].r<=r)
        return tr[p].e.push_back(i),void();
    int mid=(tr[p].l+tr[p].r)>>1;
    if(l<=mid)insert(ls,l,r,i);
    if(r>mid)insert(rs,l,r,i);
    return ;
}
inline int find(int x){
    while(x!=f[x])x=f[x];
    return x;
}
stack<pair<int,int>>st;
inline void merge(int x,int y){
    if(x==y)return ;
    if(d[x]>d[y])swap(x,y);
    st.push(make_pair(x,d[x]==d[y])),f[x]=y,d[y]+=(d[x]==d[y]);
    return ;
}
void dfs(int p,int l,int r){
    int flag=1,sz=st.size();
    for(int i:tr[p].e){
        int u=find(x[i]),v=find(y[i]);
        if(u==v){
            for(int j=l;j<=r;j++)puts("No");
            flag=0;break;
        }
        merge(find(x[i]+100005),v),merge(find(y[i]+100005),u);
    }
    if(flag){
        int mid=(tr[p].l+tr[p].r)>>1;
        if(l==r)puts("Yes");
        else dfs(ls,l,mid),dfs(rs,mid+1,r);
    }
    while(st.size()>sz)
        d[f[st.top().first]]-=st.top().second,f[st.top().first]=st.top().first,st.pop();
    return ;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>k;
    build(1,1,k);
    for(int i=1,l,r;i<=m;i++){
        cin>>x[i]>>y[i]>>l>>r;
        if(l^r)insert(1,l+1,r,i);
    }
    for(int i=1;i<=n;i++)f[i]=i,f[i+100005]=i+100005;
    dfs(1,1,k);
    return 0;
}