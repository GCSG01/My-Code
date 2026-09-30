#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e4+5,inf=1e18;
int n,m,mid,sum[N],sumi[N];
inline int w(int l,int r){
    if(l>r)return 0;
    if(l==1&&r==n)return inf;
    if(l==1)return sum[r]*(r+1)-sumi[r];
    if(r==n)return sumi[r]-sumi[l-1]-(l-1)*(sum[r]-sum[l-1]);
    int mid=(l+r)>>1;
    return sumi[mid]-sumi[l-1]-(sum[mid]-sum[l-1])*(l-1)
        +(r+1)*(sum[r]-sum[mid])-(sumi[r]-sumi[mid]);
}
int f[N],cnt[N],p[N];
inline void upd(int i,int j){
    int x=f[j]+w(j+1,i-1)+mid;
    if(x<f[i])f[i]=x,cnt[i]=cnt[j]+1,p[i]=j;
    else if(x==f[i]&&cnt[j]+1<cnt[i])
        cnt[i]=cnt[j]+1,p[i]=j;
}
void solve(int l,int r){
    if(r-l<=1)return ;
    int mid=(l+r)>>1;
    for(int i=p[l];i<=p[r];i++)
        upd(mid,i);
    solve(l,mid);
    for(int i=l+1;i<=mid;i++)
        upd(r,i);
    solve(mid,r);
}
bool check(){
    for(int i=1;i<=n+1;i++)
        f[i]=inf,cnt[i]=p[i]=0;
    upd(n+1,0);
    solve(0,n+1);
    return cnt[n+1]<=m;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m,m++;
    for(int i=1;i<=n;i++)cin>>sum[i],sumi[i]=sumi[i-1]+sum[i]*i,sum[i]+=sum[i-1];
    int l=0,r=n*100000,ans=-1;
    while(l<=r){
        mid=(l+r)>>1;
        if(check())r=mid-1,ans=mid;
        else l=mid+1;
    }
    mid=ans,check();
    cout<<f[n+1]-mid*m;
} 