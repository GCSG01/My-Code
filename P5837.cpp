#include<bits/stdc++.h>
using namespace std;
const int N=2e3+5;
int n,m;
struct node{
    int v,c,f;
};
vector<node>e[N];
int dis[N];
struct Node{
    int x,v;
    bool operator<(const Node &B)const{
        return v>B.v;
    }
};
int dij(int k){
    memset(dis,0x3f,sizeof dis);
    dis[1]=0;
    priority_queue<Node>q;q.push({1,0});
    while(!q.empty()){
        auto x=q.top();q.pop();
        for(auto y:e[x.x])
            if(y.f>=k&&dis[y.v]>dis[x.x]+y.c)
                dis[y.v]=dis[x.x]+y.c,q.push({y.v,dis[y.v]});
    }
    return dis[n];
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1,u,v,c,f;i<=m;i++)
        cin>>u>>v>>c>>f,
        e[u].push_back({v,c,f}),
        e[v].push_back({u,c,f});
    int ans=0;
    for(int k=1;k<=1000;k++){
        int sum=dij(k);
        ans=max(ans,sum=(k*1000000.0/sum-0.0000001));
    }
    cout<<ans;
    return 0;
}