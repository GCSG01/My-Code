#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,x[N],y[N],a[N],b[N];
int xl[N],xr[N],yl[N],yr[N];
int hx[N],hy[N];
int nx[N],ny[N];
bitset<N>del;
bool check(int i){
    return
    (xl[i]==-1||xl[xl[i]]==-1)&&
    (xr[i]==-1||xr[xr[i]]==-1)&&
    (yl[i]==-1||yl[yl[i]]==-1)&&
    (yr[i]==-1||yr[yr[i]]==-1);
}
void erase(int i,queue<int>&q){
    int v[8],cnt=0;
    v[cnt++]=xl[i],v[cnt++]=xr[i];
    v[cnt++]=yl[i],v[cnt++]=yr[i];
    if(xl[i]!=-1)v[cnt++]=xl[xl[i]];
    if(xr[i]!=-1)v[cnt++]=xr[xr[i]];
    if(yl[i]!=-1)v[cnt++]=yl[yl[i]];
    if(yr[i]!=-1)v[cnt++]=yr[yr[i]];
    if(xl[i]!=-1)xr[xl[i]]=xr[i];
    if(xr[i]!=-1)xl[xr[i]]=xl[i];
    if(yl[i]!=-1)yr[yl[i]]=yr[i];
    if(yr[i]!=-1)yl[yr[i]]=yl[i];
    del[i]=1;
    for(int j=0;j<cnt;j++)
        if(v[j]!=-1&&!del[v[j]]&&check(v[j]))
            q.push(v[j]);
}
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>x[i]>>y[i],
        a[i]=x[i],b[i]=y[i],
        xl[i]=xr[i]=yl[i]=yr[i]=-1,
        hx[i]=hy[i]=0,
        nx[i]=ny[i]=0,
        del[i]=0;
    sort(a+1,a+n+1),sort(b+1,b+n+1);
    int ax=unique(a+1,a+n+1)-a-1;
    int ay=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++){
        x[i]=lower_bound(a+1,a+ax+1,x[i])-a;
        y[i]=lower_bound(b+1,b+ay+1,y[i])-b;
        nx[i]=hx[x[i]];
        hx[x[i]]=i;
        ny[i]=hy[y[i]];
        hy[y[i]]=i;
    }
    for(int i=1;i<=ax;i++){
        int t[N];
        int cnt=0;
        for(int j=hx[i];j;j=nx[j])t[++cnt]=j;
        sort(t+1,t+cnt+1,[](int a,int b){return y[a]<y[b];});
        for(int j=1;j<=cnt;j++){
            if(j>1)xl[t[j]]=t[j-1];
            if(j<cnt)xr[t[j]]=t[j+1];
        }
    }
    for(int i=1;i<=ay;i++){
        int t[N];
        int cnt=0;
        for(int j=hy[i];j;j=ny[j])t[++cnt]=j;
        sort(t+1,t+cnt+1,[](int a,int b){return x[a]<x[b];});
        for(int j=1;j<=cnt;j++){
            if(j>1)yl[t[j]]=t[j-1];
            if(j<cnt)yr[t[j]]=t[j+1];
        }
    }
    queue<int>q;
    for(int i=1;i<=n;i++)
        if(check(i))
            q.push(i);
    int ans=0;
    while(q.size()){
        int u=q.front();q.pop();
        if(del[u]||!check(u))
            continue;
        erase(u,q),ans++;
    }
    if(ans==n)cout<<"YES\n";
    else cout<<"NO\n";
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--)
        solve();
}