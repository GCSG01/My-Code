#include<bits/stdc++.h>
using namespace std;
const int N=55;
struct node{
    int v;
    bool w;
};
vector<node>e[N];
int f[N];
void solve1(){
    int n,s;cin>>n>>s,s--;
    memset(f,0,sizeof f);
    for(int i=1;i<n;i++)
        if((1<<(i-1))&s)f[i]=1;
    for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        int flag=f[u]^f[v];
        if(flag)cout<<min(u,v)<<" "<<max(u,v)<<endl;
        else cout<<max(u,v)<<" "<<min(u,v)<<endl;
    }
    return ;
}
void dfs(int x,int v,int ffa){
    f[x]=v;
    for(auto y:e[x])
        if(y.v!=ffa)
            dfs(y.v,v^y.w,x);
    return ;
}
void solve2(){
    int n;cin>>n;
    memset(f,0,sizeof f);
    for(int i=1;i<=n;i++)
        e[i].clear();
    for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        e[u].push_back({v,u<v});
        e[v].push_back({u,u<v});
    }
    dfs(n,0,0);
    int ans=0;
    for(int i=1;i<n;i++)
        if(f[i])ans+=(1<<(i-1));
    cout<<ans+1<<endl;
    return ;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T,Q;cin>>T>>Q;
    if(Q==1)while(T--)solve1();
    else while(T--)solve2();
    return 0;
}