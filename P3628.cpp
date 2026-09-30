#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int n,A,B,C,a[N],sum[N];
int f[N],op[N];
inline int W(int l,int r){
    int s=sum[r]-sum[l-1];
    return A*s*s+B*s+C;
}
inline void upd(int i,int j){
    if(f[j]+W(j+1,i)>f[i])
        f[i]=f[j]+W(j+1,i),op[i]=j;
}
int cnt=0;
void solve(int l,int r){
    if(r-l<=1)return ;
    int mid=(l+r)>>1;
    for(int i=op[l];i<=op[r];i++)upd(mid,i);
    solve(l,mid);
    for(int i=l+1;i<=mid;i++)upd(r,i);
    solve(mid,r);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>A>>B>>C;
    for(int i=1;i<=n;i++)cin>>a[i],sum[i]=sum[i-1]+a[i];
    for(int i=1;i<=n;i++)f[i]=-1e18;
    upd(n,0);
    solve(0,n);
    cout<<f[n];
}