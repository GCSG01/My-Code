#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,day;
int a[N],b[N],c[N],f[N],id[N],fa[N];
bool vis[N];
vector<int>g[N];
void find_fa(int x){
    for(int y:g[x])
        if(y!=fa[x])
            fa[y]=x,find_fa(y);
}
inline __int128 get(int x,__int128 l,__int128 r){
	if(c[x]>=0)return (r-l+1)*b[x]+(r-l+1)*(l+r)/2*c[x];
	__int128 cnt=(1-b[x])/c[x];
	if(cnt<l)return r-l+1;
	if(cnt>r)return (r-l+1)*b[x]+(r-l+1)*(l+r)/2*c[x];
	return (cnt-l+1)*b[x]+(cnt-l+1)*(l+cnt)/2*c[x]+r-cnt;
}
int check(int m){
    for(int i=1;i<=n;i++){
        int l=0,r=m-1,ans=1;
        if(get(i,m,m)>=a[i]){
            f[i]=m;continue;
        }
        while(l<=r){
            int mid=(l+r)>>1;
            if(get(i,mid,m)>=a[i])ans=mid,l=mid+1;
            else r=mid-1;
        }
        f[i]=ans;
    }
    memset(vis,0,sizeof vis);
    day=0;
    for(int i=1;i<=n;i++)id[i]=i;
    sort(id+1,id+n+1,[](int A,int B){return f[A]<f[B];});
    for(int i=1;i<=n;i++){
        int x=id[i];
        while(x){
            if(vis[x])break;
            vis[x]=1,day++,x=fa[x];
        }
        if(day>f[id[i]])return false;
    }
    return true;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i]>>b[i]>>c[i];
    for(int i=1,u,v;i<n;i++)
        cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
    find_fa(1);
    int l=0,r=1e9+1,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid))r=mid-1,ans=mid;
        else l=mid+1;
    }
    cout<<ans;
}