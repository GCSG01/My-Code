#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5,inf=1e9+7;
int n,m,xx,yy;
int dis[N];
bitset<N>vis;
struct node{
    int v,w;
};
vector<node>g[N];
void add(int u,int v,int w){
    g[u].push_back({v,w});
}
struct point{
    int v,id;
    bool operator<(const point&x)const{
        return v>x.v;
    }
};
priority_queue<point>q;
int dijkstra(int s){
    for(int i=0;i<=yy;i++)dis[i]=inf;
    dis[s]=0,q.push({0,s});
    while(!q.empty()){
        auto [d,u]=q.top();
        q.pop();
        if(vis[u])continue;
        vis[u]=1;
        for(auto i:g[u])
            if(dis[i.v]>dis[u]+i.w){
                dis[i.v]=dis[u]+i.w;
                if(!vis[i.v])
                    q.push({dis[i.v],i.v});
            }
    }
    return dis[yy];
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m,xx=0,yy=(2*n-2)*(m-1)+1;
    int x,t1,t2;
    for(int i=1;i<m;i++)
        cin>>x,add(i*2,yy,x);
    for(int i=2;i<n;i++)
        for(int j=1;j<m;j++){
            cin>>x;
            t1=2*(i-2)*(m-1)-1+2*j;
            t2=2*(i-1)*(m-1)+2*j;
            add(t1,t2,x),add(t2,t1,x);
        }
    for(int i=1;i<m;i++)
        cin>>x,t1=2*(n-2)*(m-1)-1+2*i,add(xx,t1,x);

    for(int i=1;i<n;i++)
        for(int j=1;j<=m;j++){
            cin>>x,t1=2*(i-1)*(m-1)-1+2*j,t2=t1-1;
            if(j==1)
                add(xx,t1,x);
            else if(j==m)
                add(t2,yy,x);
            else add(t1,t2,x),add(t2,t1,x);
        }
    for(int i=1;i<n;i++)
        for(int j=1;j<m;j++)
            cin>>x,t1=2*(i-1)*(m-1)-1+2*j,t2=t1+1,add(t1,t2,x),add(t2,t1,x);
    cout<<dijkstra(xx);
}