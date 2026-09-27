#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5,M=8e6+5;
int n,m,p,out,sum[N];
struct node{
    int v,w;
};
vector<node>g[M];
#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
void build_in(int p,int l,int r){
    if(l==r)return;
    build_in(ls,l,mid);
    build_in(rs,mid+1,r);
    g[p].push_back({ls,0});
    g[p].push_back({rs,0});
}
void build_out(int p,int l,int r){
    g[p].push_back({p+n*4,0});
    if(l==r)return sum[l]=p+n*4,void();
    build_out(ls,l,mid);
    build_out(rs,mid+1,r);
    g[ls+n*4].push_back({p+n*4,0});
    g[rs+n*4].push_back({p+n*4,0});
}
void merge1(int p,int l,int r,int s,int t,int k){
    if(l>=s&&r<=t)
        return g[k].push_back({p,1}),
        g[p+n*4].push_back({k+1,1}),void();
    if(mid>=s)merge1(ls,l,mid,s,t,k);
    if(mid<t)merge1(rs,mid+1,r,s,t,k);
}
void merge2(int p,int l,int r,int s,int t,int k){
    if(l>=s&&r<=t)
        return g[k+1].push_back({p,1}),
        g[p+n*4].push_back({k,1}),void();
    if(mid>=s)merge2(ls,l,mid,s,t,k);
    if(mid<t)merge2(rs,mid+1,r,s,t,k);
}
int d[M];
bool vis[M];
deque<int> q;
void dijstra(int s){
    memset(d,127,sizeof(d));
    d[s]=0,q.push_front(s);
    while(!q.empty()){
        int u=q.front();q.pop_front();
        for(auto y:g[u])
            if(d[y.v]>d[u]+y.w){
                d[y.v]=d[u]+y.w;
                if(y.w==1)q.push_back(y.v);
                else q.push_front(y.v);
            }
    }
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>p;
    build_in(1,1,n),build_out(1,1,n);
    for(int a,b,c,d,i=1;i<=m;i++)
        cin>>a>>b>>c>>d,merge1(1,1,n,a,b,n*8+i*2),merge2(1,1,n,c,d,n*8+i*2);
    dijstra(sum[p]);
    for(int i=1;i<=n;i++)
        cout<<d[sum[i]]/2<<"\n";
}