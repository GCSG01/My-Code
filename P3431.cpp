#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,m,k;
struct node{
    int x,y,p;
}g[N];
int b[N],tr[N],f[N];
inline int lowbit(int x){return x&-x;}
inline void update(int x,int k){
    while(x<=m)tr[x]=max(tr[x],k),x+=lowbit(x);
}
inline int query(int x,int s=0){
    while(x)s=max(s,tr[x]),x-=lowbit(x);
    return s;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=k;i++)cin>>g[i].x>>g[i].y>>g[i].p,b[i]=g[i].y;
    sort(b+1,b+k+1),m=unique(b+1,b+k+1)-b-1;
    sort(g+1,g+k+1,[](node A,node B){return A.x==B.x?A.y<B.y:A.x<B.x;});
    for(int i=1;i<=k;i++)g[i].y=lower_bound(b+1,b+m+1,g[i].y)-b;
    for(int i=1;i<=k;i++)
        f[i]=query(g[i].y)+g[i].p,update(g[i].y,f[i]);
    int ans=0;
    for(int i=1;i<=k;i++)ans=max(ans,f[i]);
    cout<<ans;
}