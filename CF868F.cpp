#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,a[N];
int f[N][25],p[N][25];
struct node{
    int cnt[N],l,r,ans;
    node():l(1),r(0),ans(0){
        memset(a,0,sizeof a);
    }
    int upd(int s,int t){
        while(l>s)ans+=cnt[a[--l]]++;
        while(r<t)ans+=cnt[a[++r]]++;
        while(l<s)ans-=--cnt[a[l++]];
        while(r>t)ans-=--cnt[a[r--]];
        return ans;
    }
}A,B;
inline void check(int i,int j,int k,node &x){
    int v=f[j][k-1]+x.upd(j+1,i);
    if(v<f[i][k])f[i][k]=v,p[i][k]=j;
}
void solve(int l,int r,int k){
    if(r-l<=1)return ;
    int mid=(l+r)>>1;
    for(int i=p[l][k];i<=p[r][k];i++)
        check(mid,i,k,A);
    solve(l,mid,k);
    for(int i=l+1;i<=mid;i++)
        check(r,i,k,B);
    solve(mid,r,k);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int k;cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    memset(f,0x3f,sizeof f);
    f[0][0]=0;
    for(int i=1;i<=k;i++)
        check(n,0,i,A),solve(0,n,i);
    cout<<f[n][k];
}