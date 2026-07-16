#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m;
vector<int>e[N];
int w[N],vis[N],idx,dfn[N],low[N];
void tarjan(int x){
    dfn[x]=low[x]=++idx,w[x]=-1;
    for(auto y:e[x])
        if(y!=fa)
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1,u,v;i<=m;i++)
        cin>>u>>v,e[u].push_back(v),e[v].push_back(u);
    for(int i=1;i<=n;i++)
        if(!dfn[i])tarjan(i,0),dfs(i,0);
    return 0;
}