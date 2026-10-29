#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,M=2*N,LOG=20;
int n,q;
vector<int>g[N];
int dep[N],fa[LOG][N],tin[N],tout[N],first[N],timer;
int euler[M],lg[M],rmq[LOG][M],ecnt;
int s[N],vis[N],tot,stx[N],ste[N];
void dfs(){
	int top=1;
	stx[top]=1,ste[top]=0;
	dep[1]=1,tin[1]=++timer,first[1]=ecnt;
	euler[ecnt++]=1;
	while(top){
		int x=stx[top];
		int &i=ste[top];
		while(i<(int)g[x].size()&&g[x][i]==fa[0][x])i++;
		if(i==(int)g[x].size()){
			tout[x]=timer,top--;
			if(top)euler[ecnt++]=stx[top];
			continue;
		}
		int y=g[x][i++];
		if(y==fa[0][x])continue;
		fa[0][y]=x,dep[y]=dep[x]+1;
		for(int j=1;j<LOG;j++)fa[j][y]=fa[j-1][fa[j-1][y]];
		tin[y]=++timer,first[y]=ecnt;
		euler[ecnt++]=y;
		stx[++top]=y,ste[top]=0;
	}
	for(int i=2;i<=ecnt;i++)lg[i]=lg[i>>1]+1;
	for(int i=0;i<ecnt;i++)rmq[0][i]=euler[i];
	for(int j=1;j<LOG;j++)
		for(int i=0;i+(1<<j)<=ecnt;i++){
			int x=rmq[j-1][i],y=rmq[j-1][i+(1<<(j-1))];
			rmq[j][i]=dep[x]<dep[y]?x:y;
		}
}
int LCA(int x,int y){
	int l=first[x],r=first[y];
	if(l>r)swap(l,r);
	int j=lg[r-l+1];
	int a=rmq[j][l],b=rmq[j][r-(1<<j)+1];
	return dep[a]<dep[b]?a:b;
}
inline int dist(int x,int y){
	return dep[x]+dep[y]-2*dep[LCA(x,y)];
}
bool inside(int u,int root){
	return tin[root]<=tin[u]&&tout[u]<=tout[root];
}
int jump(int x,int k){
	for(int i=0;i<LOG;i++)
		if(k>>i&1)x=fa[i][x];
	return x;
}
bool check(int k,int D){
	tot++;
	for(int cnt=0;cnt<3;cnt++){
		int idx=0;
		while(idx<k&&vis[idx]==tot)++idx;
		if(idx==k)return true;
		if(cnt==2)return false;
		int x=s[idx],w,son=0;
		if(!(D&1))w=jump(x,min(D/2,dep[x]-1));
		else if(dep[x]>(D+1)/2)
			son=jump(x,(D-1)/2),w=fa[0][son];
		else w=1;
		for(int i=0;i<k;i++)
			if(vis[i]!=tot){
				int sum;
				if(son){
					if(inside(s[i],son))sum=2*dist(s[i],son)+1;
					else sum=2*dist(s[i],fa[0][son])+1;
				}
				else sum=2*dist(s[i],w);
				if(sum<=D)vis[i]=tot;
			}
	}
	return false;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>q;
	for(int i=1,u,v;i<n;i++)
		cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	dfs();
	while(q--){
		int k;cin>>k;
		for(int i=0;i<k;i++)cin>>s[i];
		sort(s,s+k,[](int a,int b){return dep[a]>dep[b];});
		int l=0,r=2*n;
		while(l<r){
			int mid=(l+r)>>1;
			if(check(k,mid))r=mid;
			else l=mid+1;
		}
		cout<<r<<"\n";
	}
}
