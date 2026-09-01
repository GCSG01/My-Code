#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,inf=1e18;
int n,m;
int dis[N];
struct node{
    int t,l,r,c;
    bool operator<(const node &B)const{
        return t<B.t;
    }
}a[N];
#define ls p<<1
#define rs p<<1|1
#define mid ((l+r)>>1)
int tr[2][N<<2];
void push_up(int c,int p){
    tr[c][p]=min(tr[c][ls],tr[c][rs]);
}
void build(int l,int r,int p){
    if(l==r)
        return tr[0][p]=a[l].l+a[l].t,tr[1][p]=a[l].l-a[l].t,void();
    build(l,mid,ls),build(mid+1,r,rs);
    push_up(0,p),push_up(1,p);
}
vector<int>v;
void query(int c,int l,int r,int p,int s,int t,int x){
    if(s>r||t<l)return;
    if(tr[c][p]>x+1)return ;
    if(l==r)
        return v.push_back(l),tr[0][p]=tr[1][p]=inf,void();
    if(s<=mid)query(c,l,mid,ls,s,t,x);
    if(t>mid)query(c,mid+1,r,rs,s,t,x);
    push_up(0,p),push_up(1,p);
}
void dij(){
    memset(dis,0x3f,sizeof dis);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
    for(int i=1;i<=m;i++)
        if(a[i].l==1)q.push({a[i].c,i}),dis[i]=a[i].c;
    build(1,m,1);
    while(!q.empty()){
        auto [d,x]=q.top();q.pop();
        if(dis[x]!=d)continue;
        v.clear();
        int pos=lower_bound(a+1,a+m+1,a[x])-a;
        if(pos>1)query(1,1,m,1,1,pos-1,a[x].r-a[x].t);
        query(0,1,m,1,pos,m,a[x].r+a[x].t);
        for(auto y:v)
            if(dis[y]>dis[x]+a[y].c)
                dis[y]=dis[x]+a[y].c,q.push({dis[y],y});
    }
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++)
        cin>>a[i].t>>a[i].l>>a[i].r>>a[i].c;
    sort(a+1,a+m+1);
    dij();
    int ans=inf;
    for(int i=1;i<=m;i++)
        if(a[i].r==n)
            ans=min(ans,dis[i]);
    // for(int i=1;i<=m;i++)
    //     cout<<dis[i]<<" ";
    // cout<<"\n";
    if(ans==inf)cout<<-1;
    else cout<<ans;
    return 0;
}