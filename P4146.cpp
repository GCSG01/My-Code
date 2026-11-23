#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e4+5,inf=1e18;
int n,m;
int ls[N],rs[N],siz[N],key[N],val[N],mx[N],tag[N],rev[N];
int tot,rt;
mt19937 rnd(time(0));
inline int newnode(){
	return tot++,siz[tot]=1,key[tot]=rnd(),tot;
}
inline void push_up(int p){
	siz[p]=siz[ls[p]]+siz[rs[p]]+1,mx[p]=max({mx[ls[p]],mx[rs[p]],val[p]});
}
inline void push_down(int p){
	if(rev[p])
		rev[ls[p]]^=1,rev[rs[p]]^=1,swap(ls[p],rs[p]),rev[p]=0;
	if(tag[p]){
		val[ls[p]]+=tag[p],val[rs[p]]+=tag[p];
		mx[ls[p]]+=tag[p],mx[rs[p]]+=tag[p],
		tag[ls[p]]+=tag[p],tag[rs[p]]+=tag[p],
		tag[p]=0;
	}
}
void split(int p,int v,int &x,int &y){
	if(!p)return x=y=0,void();
	push_down(p);
	if(siz[ls[p]]>=v)
		split(ls[p],v,x,ls[y=p]);
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
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m,mx[0]=-inf;
	for(int i=1;i<=n;i++)rt=merge(rt,newnode());
	while(m--){
		int op,l,r,v;cin>>op>>l>>r;
		if(op==1){
			cin>>v;
			int x,y,z;split(rt,r,x,z),split(x,l-1,x,y);
			val[y]+=v,tag[y]+=v,mx[y]+=v,rt=merge(x,merge(y,z));
		}
		else if(op==2){
			int x,y,z;split(rt,r,x,z),split(x,l-1,x,y);
			rev[y]^=1,rt=merge(x,merge(y,z));
		}
		else{
			int x,y,z;split(rt,r,x,z),split(x,l-1,x,y);
			cout<<mx[y]<<"\n",rt=merge(x,merge(y,z));
		}
	}
}