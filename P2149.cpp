#include<bits/stdc++.h>
using namespace std;
const int N=5e3+5,inf=1e9+7;
int n,m,ans;
int dis[4][N],f[N],f2[N];
int in[N],q[N];
struct node{
	int v,w;
};
vector<node>g[N];
set<pair<int,int>>h;
void add(int u,int v,int w){
	g[u].push_back({v,w}),g[v].push_back({u,w});
}
void dijkstra(int s,int k){
	for(int i=1;i<=n;i++)dis[k][i]=inf;
	dis[k][s]=0,h.insert({0,s});
	while(!h.empty()){
		auto [d,u]=*h.begin();
		h.erase(h.begin());
		if(d!=dis[k][u])continue;
		for(auto i:g[u]){
            if(dis[k][u]+i.w<dis[k][i.v]){
                auto [v,w]=i;
				if(dis[k][v]!=inf)
					h.erase({dis[k][v],v});
				dis[k][v]=dis[k][u]+w;
				h.insert({dis[k][v],v});
			}
		}
	}
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int s1,t1,s2,t2;cin>>n>>m>>s1>>t1>>s2>>t2;
    for(int i=1,u,v,w;i<=m;i++)
        cin>>u>>v>>w,add(u,v,w);
    dijkstra(s1,0),dijkstra(t1,1);
    dijkstra(s2,2),dijkstra(t2,3);
    for(int u=1;u<=n;u++)
        for(auto i:g[u])
            if(dis[0][u]+i.w+dis[1][i.v]==dis[0][t1])
                in[i.v]++;
    int l=1,r=1;q[r++]=s1;
    while(l<r){
        int u=q[l++];
        ans=max(ans,max(f[u],f2[u]));
        for(auto i:g[u]){
            auto [v,w]=i;
            if(dis[0][u]+w+dis[1][v]!=dis[0][t1])continue;
            in[v]--;
            if(dis[2][u]+w+dis[3][v]==dis[2][t2])
                f[v]=max(f[v],f[u]+w);
            if(dis[3][u]+w+dis[2][v]==dis[2][t2])
                f2[v]=max(f2[v],f2[u]+w);
            if(!in[v])q[r++]=v;
        }
    }
    cout<<ans;
}