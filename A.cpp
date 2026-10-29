#include<bits/stdc++.h>
using namespace std;
const int N=20,M=1<<N;
int n,m,adj[N],pc[M],path[M],cyc[M],seen[M],cnt[N+2],st[N+2],pos[N+2],girth,best;
unsigned seed;
inline unsigned rnd(){seed^=seed<<13;seed^=seed>>17;seed^=seed<<5;return seed;}
void prepare(){
	int lim=1<<n;
	fill(cnt,cnt+N+2,0);
	for(int s=1;s<lim;s++){
		int rt=s&-s;
		if(s==rt)path[s]=s;
		else{
			int e=0;
			for(int x=s^rt;x;x&=x-1){
				int b=x&-x,v=__builtin_ctz((unsigned)b);
				if(path[s^b]&adj[v])e|=b;
			}
			path[s]=e;
			if(pc[s]>=3&&(e&adj[__builtin_ctz((unsigned)rt)]))cnt[pc[s]]++;
		}
	}
	st[3]=0;
	for(int l=3;l<=n;l++)st[l+1]=st[l]+cnt[l];
	for(int l=3;l<=n;l++)pos[l]=st[l];
	for(int s=1;s<lim;s++)
		if(pc[s]>=3&&(path[s]&adj[__builtin_ctz((unsigned)(s&-s))]))
			cyc[pos[pc[s]]++]=s;
	girth=n+1;
	for(int l=3;l<=n;l++)if(st[l+1]-st[l]){girth=l;break;}
	for(int l=girth;l<=n;l++)
		for(int i=st[l+1]-1;i>st[l];i--)
			swap(cyc[i],cyc[st[l]+rnd()%(i-st[l]+1)]);
}
bool dfs(int used,int q){
	best=max(best,q);
	if(girth>n)return 0;
	int bound=used?q+(n-pc[used])/(girth-1):(n-1)/(girth-1);
	if(best>=bound)return best==(n-1)/(girth-1);
	if(seen[used]>=q)return 0;
	seen[used]=q;
	for(int l=girth;l<=n;l++)
		for(int z=st[l];z<st[l+1];z++){
			int c=cyc[z];
			if(pc[c&used]>1)continue;
			int nu=used|c;
			if(nu!=used&&dfs(nu,q+1))return 1;
		}
	return 0;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	freopen("cactus.in","r",stdin);
	freopen("cactus.out","w",stdout);
	int C,T;cin>>C>>T;
	while(T--){
		cin>>n>>m;memset(adj,0,sizeof adj);
		for(int i=0,u,v;i<m;i++)
			cin>>u>>v,u--,v--,adj[u]|=1<<v,adj[v]|=1<<u;
		int vis=1,stk[N],top=1;stk[0]=0;
		while(top){
			int u=stk[--top];
			for(int x=adj[u]&~vis;x;x&=x-1){
				int b=x&-x;vis|=b;stk[top++]=__builtin_ctz((unsigned)b);
			}
		}
		if(vis!=(1<<n)-1){cout<<-1<<'\n';continue;}
		int lim=1<<n;pc[0]=0;
		for(int s=1;s<lim;s++)pc[s]=pc[s>>1]+(s&1);
		fill(seen,seen+lim,-1);
		seed=(unsigned)chrono::steady_clock::now().time_since_epoch().count()^(unsigned)(T*1199540897U);
		prepare();best=0;
		if(girth<=n)dfs(0,0);
		cout<<m-(n-1+best)<<'\n';
	}
}
/*
1.原图不连通时无解。
2.连通仙人掌若有q个环,边数为n-1+q,所以要最大化环数。
3.用子集DP求每个顶点集合是否能组成简单环。path[S]表示从S中最小点出发的哈密顿路径可能终点集合,复杂度O(n*2^n)。
4.随机打乱候选环,DFS逐个加入环,要求新环与已选顶点交集不超过一个点,并用最短环长度剪枝。
5.选出的环可用原图中的树边连接成生成仙人掌,答案为m-(n-1-q)。
*/
