#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5,inf=1e18;
int n,m;
int dis[N],tot[N];
struct node{
    int v,w;
};
vector<node>g[N];
bitset<N>vis;
queue<int>q;
inline void add(int u,int v,int w){
    g[u].push_back({v,w});
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int op,a,b,c;cin>>op>>a>>b;
        if(op==1)cin>>c,add(b,a,c);
        else if(op==2)cin>>c,add(a,b,-c);
        else add(a,b,0),add(b,a,0);
    }
    for(int i=1;i<=n;i++)add(0,i,0),dis[i]=inf;
    memset(dis,-0x3f,sizeof(dis));
    dis[0]=0,vis[0]=1,q.push(0);
    while (!q.empty()){
    int u=q.front();q.pop();
    vis[u]=0;
    for(auto [v,w]:g[u])
        if(dis[u]+w>dis[v]){
            dis[v]=dis[u]+w;
            if(!vis[v]){
                vis[v]=1,q.push(v),tot[v]++;
                if(tot[v]>=n)
                    return cout<<"No",0;
            }
        }
    }
    cout<<"Yes";
}