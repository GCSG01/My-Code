#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+5;
int n,m;
vector<int>g[N];
int dfn[N],low[N],tot;
int st[N],top,root;
bitset<N>vis;
int ans=0;
void tarjan(int x,int fa){
	dfn[x]=low[x]=++tot,st[++top]=x;
	int flag=0;
	for(int y:g[x])
		if(!dfn[y]){
			tarjan(y,0),low[x]=min(low[x],low[y]);
			if((low[y]>=dfn[x]&&root!=x)||(root==x&&flag>0)){
				int sum=0;
				while(st[top]!=y)
					sum++,top--;
				sum++,top--;
				ans+=sum*(sum+1)/2;
				vis[x]=1;
			}
			flag++;
		}
		else if(y!=fa)low[x]=min(low[x],dfn[y]);
	if(root==x&&top){
		int sum=0;
		while(st[top]!=x)
			sum++,top--;
		sum++,top--;
		ans+=sum*(sum-1)/2;
		vis[x]=1;
	}
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++)cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	for(int i=1;i<=n;i++)
		if(!dfn[i])root=i,tarjan(i,0);
	cout<<ans;
}