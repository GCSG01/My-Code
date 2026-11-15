#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a[35005],dp[35005][55],p[35005][55];
struct node{
    int l=1,r=0,sum=0;
    int vis[35005];
    void add(int x){
        if(!vis[x]) sum++;
        vis[x]++;
    }
    void del(int x){
        vis[x]--;
        if(!vis[x]) sum--;
    }
    int query(int L,int R){
        while(r<R) add(a[++r]);
        while(r>R) del(a[r--]);
        while(l<L) del(a[l++]);
        while(l>L) add(a[--l]);
        return sum;
    }
}md;
void upd(int i,int j,int k,node &x){
    int val=dp[j][k-1]+x.query(j+1,i);
    if(val>dp[i][k]){
        dp[i][k]=val;
        p[i][k]=j;
    }
}
void solve(int l,int r,int k){
    if(r-l<=1) return ;
    int mid=(l+r)>>1;
    for(int i=p[l][k];i<=p[r][k];i++) upd(mid,i,k,md);
    solve(l,mid,k);
    for(int i=l+1;i<=mid;i++) upd(r,i,k,md);
    solve(mid,r,k);
}
signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=k;i++){
        solve(0,n,i);
    }
    cout<<dp[n][k];
    return 0;
}