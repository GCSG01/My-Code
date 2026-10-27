#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,mod=1e9+7;
struct Treap{
	struct node{
		int l=0,r=0,sz=1,pri=0;
		int val=0,mul=1,add=0;
	};
	vector<node>tr;
	#define ls(p) tr[p].l
	#define rs(p) tr[p].r
	unsigned int seed=712367821u;
	Treap(int n=0){
		tr.reserve(n+5),tr.push_back(node());
	}
	int rnd(){
		seed^=seed<<13ull;
		seed^=seed>>17ull;
		seed^=seed<<5ull;
		return seed;
	}
	int size(int x){
		return x?tr[x].sz:0ll;
	}
	void push_up(int x){
		if(!x)return ;
		tr[x].sz=1+size(ls(x))+size(rs(x));
	}
	void upd(int x,int m,int a){
		if(!x)return;
		tr[x].val=(tr[x].val*m+a)%mod;
		tr[x].mul=tr[x].mul*m%mod;
		tr[x].add=(tr[x].add*m+a)%mod;
	}
	void push_down(int x){
		if(!x)return;
		if(tr[x].mul==1&&!tr[x].add)return;
		upd(ls(x),tr[x].mul,tr[x].add);
		upd(rs(x),tr[x].mul,tr[x].add);
		tr[x].mul=1;
		tr[x].add=0;
	}
	int nwnode(int v){
		node x;
		x.val=v%mod;
		x.pri=rnd();
		tr.push_back(x);
		return (int)tr.size()-1;
	}
	int merge(int x,int y){
		if(!x||!y)return x+y;
		if(tr[x].pri>tr[y].pri)
			return push_down(x),tr[x].r=merge(tr[x].r,y),push_up(x),x;
		return push_down(y),tr[y].l=merge(x,tr[y].l),push_up(y),y;
	}
	void split(int x,int k,int &a,int &b){
		if(!x)return a=b=0,void();
		push_down(x);
		if(size(ls(x))>=k)
			split(ls(x),k,a,ls(x)),push_up(x),b=x;
		else
			split(rs(x),k-size(ls(x))-1,rs(x),b),push_up(x),a=x;
	}
	void update(int &root,int l,int r,int m,int a){
		if(l>r||!root)return;
		int x,y,z;
		split(root,r,x,z);
		split(x,l-1,x,y);
		upd(y,m%mod,a%mod);
		root=merge(merge(x,y),z);
	}
	void modify(int x,int k,int m,int a){
		if(!x)return;
		push_down(x);
		int lsiz=size(ls(x));
		if(k==lsiz+1)
			return tr[x].val=(tr[x].val*m%mod+a)%mod,void();
		if(k<=lsiz) modify(ls(x),k,m,a);
		else modify(rs(x),k-lsiz-1,m,a);
	}
	void calc(int x,int &cnt,int *a){
		if(!x)return;
		push_down(x);
		calc(tr[x].l,cnt,a);
		a[cnt++]=tr[x].val;
		calc(tr[x].r,cnt,a);
	}
};
namespace Segment_Tree{
	int tr[N<<2],n=1;
	void init(int m){
		n=1;
		while(n<m)n<<=1;
		for(int i=1;i<(n<<1);i++)tr[i]=1;
	}
	#define ls (p<<1)
	#define rs (p<<1|1)
	void insert(int p,int v){
		tr[p+=n]=v%mod;
		while(p>>=1)
			tr[p]=tr[ls]*tr[rs]%mod;
	}
	int update(int l,int r){
		int x=1,y=1;
		l+=n,r+=n;
		while(l<r){
			if(l&1)x=x*tr[l++]%mod;
			if(r&1)y=tr[--r]*y%mod;
			l>>=1,r>>=1;
		}
		return x*y%mod;
	}
}
using Segment_Tree::init;
using Segment_Tree::insert;
using Segment_Tree::update;
using Segment_Tree::tr;
int n;
vector<int>g[N];
int fa[N],dep[N],rt[N];
int son[N],f[N],tmp[N];
struct event{
    int k,id,val;
}ev[N];
void dfs(int v,int ffa,Treap &top){
	fa[v]=ffa,dep[v]=0;
	for(int u:g[v])
		if(u!=ffa)
			dfs(u,v,top);
	int heavy=0;
	for(int u:g[v])
		if(fa[u]==v&&dep[u]>dep[heavy])
			heavy=u;
	int root=0;
	if(heavy)
		root=rt[heavy],dep[v]=dep[heavy]+1;
	root=top.merge(top.nwnode(1),root);
	if(heavy)
		top.update(root,2,top.size(root),1,1);
	for(int u:g[v])
		if(fa[u]==v&&u!=heavy){
			int cnt=0;
			top.calc(rt[u],cnt,tmp);
			for(int j=0;j<=dep[u];j++)
				top.modify(root,j+2,(tmp[j]+1)%mod,0);
			top.update(root,dep[u]+3,dep[v]+1,1+tmp[dep[u]],0);
		}
	rt[v]=root;
}
int solve(){
	cin>>n;
	for(int i=1;i<=n;i++)g[i].clear(),rt[i]=son[i]=f[i]=tmp[i]=0;
	for(int i=1,u,v;i<n;i++)
		cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	Treap top(n+5);
	dep[0]=-1;
	for(int u:g[1])
		dfs(u,1,top);
	int m=0;
	for(int u:g[1])son[++m]=u;
	int tot=0;
	for(int i=1;i<=m;i++){
		int cnt=0;
		top.calc(rt[son[i]],cnt,tmp);
		for(int k=0;k<cnt;k++)
			ev[++tot]={k+1,i-1,(1+tmp[k])%mod};
	}
	sort(ev+1,ev+tot+1,[](event A,event B){return A.k<B.k;});
	init(m);
	for(int i=0;i<m;i++)
		f[i]=1,insert(i,1);
	int ans=1;
	for(int i=1;i<=tot;){
		int lst=tr[1],sum=0,r=i;
		while(r<=tot&&ev[r].k==ev[i].k){
			int x=ev[r].id;
			sum+=(ev[r].val-f[x])%mod*update(0,x)%mod*update(x+1,m)%mod,sum%=mod;
			r++;
		}
		for(int j=i;j<r;j++){
			int x=ev[j].id;
			f[x]=ev[j].val,insert(x,f[x]);
		}
		ans+=tr[1]-lst-sum,ans%=mod;
		i=r;
	}
	if(ans<0)ans+=mod;
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	// freopen("game.in","r",stdin);
	// freopen("game.out","w",stdout);
	int T;cin>>T;
	for(int i=1;i<=T;i++)
		cout<<"Case #"<<i<<": "<<solve()<<"\n";
}