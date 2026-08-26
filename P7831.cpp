#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,inf=1e9;
int n,m;
int ans[N],ou[N],vis[N];
struct node{
    int u,v,r,p;
}e[N];
vector<int>g[N];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)ans[i]=inf;
    for(int i=1;i<=m;i++)
        cin>>e[i].u>>e[i].v>>e[i].r>>e[i].p,ou[e[i].u]++;
    sort(e+1,e+m+1,[](node A,node B){return A.r>B.r;});
    for(int i=1;i<=m;i++)
        g[e[i].v].push_back(i);
    queue<int>q;
	for(int i=1;i<=n;i++)
        if(!ou[i])q.push(i);
	for(int i=1;i<=m;i++){
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int v:g[u])
                if(!vis[v]){
                    vis[v]=1,ou[e[v].u]--;
                    if(!ou[e[v].u])
                        q.push(e[v].u);
                    if(ans[u]!=inf)
                        ans[e[v].u]=min(ans[e[v].u],max(e[v].r,ans[u]-e[v].p));
                }
		}
		if(!vis[i]){
			vis[i]=1,ou[e[i].u]--;
			if(!ou[e[i].u])q.push(e[i].u);
			ans[e[i].u]=min(ans[e[i].u],e[i].r);
		}
	}
	for(int i=1;i<=n;i++)
        cout<<(ans[i]==inf?-1:ans[i])<<" ";
    return 0;
}