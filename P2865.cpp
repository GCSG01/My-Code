#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m;
int dis1[N],dis2[N],vis[N];
struct node{
    int v,w;
};
vector<node>g[N];
queue<int>q;
inline void add(int u,int v,int w){
    g[u].push_back({v,w});
}
void dij(){
    memset(dis1,0x3f,sizeof dis1);
    memset(dis2,0x3f,sizeof dis2);
    dis1[1]=0,vis[1]=1;
    q.push(1);
    while(!q.empty()){
        int x=q.front();q.pop(),vis[x]=0;;
        for(auto y:g[x]){
			if(dis1[y.v]>dis1[x]+y.w){
				dis2[y.v]=dis1[y.v],dis1[y.v]=dis1[x]+y.w;
				if(!vis[y.v])vis[y.v]=1,q.push(y.v);
			}
			if(dis2[y.v]>dis1[x]+y.w&&dis1[x]+y.w>dis1[y.v]){
				dis2[y.v]=dis1[x]+y.w;
				if(!vis[y.v])vis[y.v]=1,q.push(y.v);
			}
			if(dis2[y.v]>dis2[x]+y.w){
				dis2[y.v]=dis2[x]+y.w;
				if(!vis[y.v])vis[y.v]=1,q.push(y.v);
			}
        }
    }
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1,u,v,w;i<=m;i++)
        cin>>u>>v>>w,add(u,v,w),add(v,u,w);
    dij();
    cout<<dis2[n];
}