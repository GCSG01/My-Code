#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5,inf=1e18;
struct node{
	int pre,suf,mx,sum;
	inline void cover(int x,int len){
		sum=x*len,pre=suf=mx=x<0?x:sum;
	}
	friend node operator+(node a,node b){
		return{
			max(a.pre,a.sum+b.pre),
			max(b.suf,b.sum+a.suf),
			max({a.mx,b.mx,a.suf+b.pre}),
			a.sum+b.sum
		};
	}
}tr[N];
mt19937 rnd(time(0));
int ls[N],rs[N],siz[N];
int key[N],val[N],tag[N],cov[N];
int stk[N],top,tot=0;
int rt,R;
inline int newnode(int x){
	int p=top?stk[top--]:++tot;
	siz[p]=1,val[p]=x,key[p]=rand();
	tr[p]={x,x,x,x},cov[p]=inf;
	return p;
}
inline void delet(int x){
	siz[x]=ls[x]=rs[x]=val[x]=key[x]=tag[x]=0,tr[x]={-inf,-inf,-inf,0},stk[++top]=x;
}
inline void push_up(int x){
	siz[x]=siz[ls[x]]+siz[rs[x]]+1,tr[x]=tr[ls[x]]+(node){val[x],val[x],val[x],val[x]}+tr[rs[x]];
}
inline void push_down(int x){
	if(tag[x]){
		tag[ls[x]]^=1,tag[rs[x]]^=1;
		swap(tr[ls[x]].pre,tr[ls[x]].suf);
		swap(tr[rs[x]].pre,tr[rs[x]].suf);
		swap(ls[x],rs[x]),tag[x]=0;
	}
	if(cov[x]!=inf){
		val[ls[x]]=val[rs[x]]=cov[ls[x]]=cov[rs[x]]=cov[x];
		tr[ls[x]].cover(cov[x],siz[ls[x]]),
		tr[rs[x]].cover(cov[x],siz[rs[x]]);
		cov[x]=inf;
	}
}
void split(int p,int v,int &x,int &y){
	if(!p)return x=y=0,void();
	push_down(p);
	if(siz[ls[p]]>=v)split(ls[p],v,x,ls[y=p]);
	else split(rs[p],v-siz[ls[p]]-1,rs[x=p],y);
	push_up(p);
}
int merge(int x,int y){
	if(!x||!y)return x+y;
	push_down(x),push_down(y);
	if(key[x]>key[y])
		return rs[x]=merge(rs[x],y),push_up(x),x;
	return ls[y]=merge(x,ls[y]),push_up(y),y;
}
void clear(int x){
	if(!x)return ;
	clear(ls[x]),clear(rs[x]),delet(x);
}
inline void split(int &x,int &y,int &z){
	int p,t;cin>>p>>t,p--;
	split(R,p+t,x,z),split(x,p,x,y);
}
inline void merge(int x,int y,int z){
	R=merge(merge(x,y),z);
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,m;cin>>n>>m,tr[0]={-inf,-inf,-inf,0};
	for(int i=1,x;i<=n;i++)
		cin>>x,R=merge(R,newnode(x));
	while(m--){
		string s;cin>>s;
		int x=0,y=0,z=0;
		if(s[0]=='I'){
			int p,tot,rt=0;cin>>p>>tot;
			for(int i=1;i<=tot;i++)
				cin>>x,rt=merge(rt,newnode(x));
			x=y=0,split(R,p,x,y),R=merge(merge(x,rt),y);
		}
		else if(s[0]=='D')
			split(x,y,z),clear(y),R=merge(x,z);
		else if(s[0]=='R')
			split(x,y,z),tag[y]^=1,merge(x,y,z);
		else if(s[0]=='G')
			split(x,y,z),cout<<tr[y].sum<<"\n",merge(x,y,z);
		else if(s[2]=='K')
			split(x,y,z),cin>>cov[y],val[y]=cov[y],
			tr[y].cover(val[y],siz[y]),merge(x,y,z);
		else cout<<tr[R].mx<<"\n";
	}
}