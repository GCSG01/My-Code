#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int n,k;
struct node{
    int v,w;
};
vector<node>g[N];
int f[N][500][3];
void dfs(int x,int ffa){
    for(auto y:g[x])
        if(y.v!=ffa)
            dfs(y.v,x);
    return ;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    memset(f,-0x3f,sizeof f);
    cin>>n>>k;
    for(int i=1;i<n;i++){
        int u,v,w;cin>>u>>v>>w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    for(int i=1;i<=n;i++)
        f[i][0][0]=f[i][1][2]=0;
    dfs(1,0);
    return 0;
}