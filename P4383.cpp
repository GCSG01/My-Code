#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=6e5+5,inf=1145141919810;
int n,k;
struct edge{
    int v,w;
};
vector<edge>g[N];
struct node{
    int v,k;
    friend bool operator <(node a,node b){
        return (a.v==b.v)?a.k>b.k:a.v<b.v;
    }
    friend node operator +(node a,node b){
        return {a.v+b.v,a.k+b.k};
    }
}dp[N][3],tr[3];
int mid;
inline void dfs(int x,int ffa){
    for(auto y:g[x]){
        if(y.v==ffa)continue;
        dfs(y.v,x);
        for(int j=0;j<3;j++)
            tr[j]={-inf,inf};
        for(int j=0;j<3;j++)
            tr[0]=max(tr[0],dp[x][0]+dp[y.v][j]);
        for(int j=0;j<3;j++)
            tr[1]=max(tr[1],dp[x][1]+dp[y.v][j]);
        for(int j=0;j<3;j++)
            tr[2]=max(tr[2],dp[x][2]+dp[y.v][j]);
        tr[1]=max(tr[1],dp[x][0]+dp[y.v][0]+(node){y.w-mid,1});
        tr[1]=max(tr[1],dp[x][0]+dp[y.v][1]+(node){y.w,0});
        tr[2]=max(tr[2],dp[x][1]+dp[y.v][1]+(node){y.w+mid,-1});
        tr[2]=max(tr[2],dp[x][1]+dp[y.v][0]+(node){y.w,0});
        for(int j=0;j<3;j++)
            dp[x][j]=tr[j];
    }
}
inline void init(){
    for(int i=1;i<=n;i++)
        dp[i][0]={0,0},dp[i][1]={-inf,inf},dp[i][2]={-mid,1};
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>k;
    for(int i=1,u,v,w;i<n;i++){
        cin>>u>>v>>w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    int l=-1e12,r=1e12;
    while(l<=r){
        mid=(l+r)/2;
        init(),dfs(1,0);
        auto ans=max({dp[1][0],dp[1][1],dp[1][2]});
        if(ans.k>k+1)l=mid+1;
        else if(ans.k==k+1)return cout<<max({dp[1][0],dp[1][1],dp[1][2]}).v+(k+1)*mid,0;
        else r=mid-1;
    }
    mid=l;
    init(),dfs(1,0);
    cout<<max({dp[1][0],dp[1][1],dp[1][2]}).v+(k+1)*mid;
}