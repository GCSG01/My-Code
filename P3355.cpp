#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5;
int n,m,s,t;
struct edge{
	int v,nxt,val;
}e[N];
int head[N],cnt=1,cur[N];
int ans;
bool b[1005][1005];
int dis[N];
int dx[]={1,1,-1,-1,2,2,-2,-2};
int dy[]={2,-2,2,-2,1,-1,1,-1};
int Read(){
	int ch=0;
	char w=getchar();
	while(w<'0'||w>'9') w=getchar();
	while(w>='0'&&w<='9'){
		ch=ch*10+w-'0';
		w=getchar();
	}
	return ch;
}
void add(int u,int v,int val){
	e[++cnt]=(edge){v,head[u],val};head[u]=cnt;
	e[++cnt]=(edge){u,head[v],0};head[v]=cnt;
}
bool bfs(){
	queue<int>q;
	memset(dis,-1,sizeof(dis));
	dis[s]=1;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].v;
			if(dis[v]==-1&&e[i].val){
				q.push(v);
				dis[v]=dis[u]+1;
			}
		}
	}
	return dis[t]!=-1;
}
int dfs(int u,int flow){
	if(u==t) return flow;
	int res=0;
	for(int i=cur[u];i;i=e[i].nxt){
		cur[u]=i;int v=e[i].v;
		if(dis[v]==dis[u]+1&&e[i].val){
			int fl=dfs(v,min(flow,e[i].val));
			if(fl){
				flow-=fl;res+=fl;
				e[i].val-=fl;e[i^1].val+=fl;
				if(!flow) return res;
			}
		}
	}
	if(!res) dis[u]=-1;
	return res;
}
int main(){
	n=Read();m=Read();
	ans=n*n-m;
	s=n*n+1;t=s+1;
	for(int i=1;i<=m;i++){
		int x,y;
		x=Read();y=Read();
		b[x][y]=1;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(b[i][j]==1) continue;
			if((i+j)%2==1) add(s,(i-1)*n+j,1);
			if((i+j)%2==0) add((i-1)*n+j,t,1);
		}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if((i+j)%2==0) continue;
			if(b[i][j]==1) continue;
			for(int k=0;k<8;k++){
				int xx=dx[k]+i;
				int yy=dy[k]+j;
				if(xx<1||xx>n||yy<1||yy>n||b[xx][yy]==1) continue;
				add((i-1)*n+j,(xx-1)*n+yy,1e9);
			}
		}
	}
	while(bfs()){
		memcpy(cur,head,sizeof(head));
		ans-=dfs(s,1<<29);	
	}
	cout<<ans;
	return 0;
}