#include<bits/stdc++.h>
// #define int long long
using namespace std;
const int N=1.3e6+5,inf=1e9+7;
mt19937 rnd(time(0));
int n,m;
namespace FHQ_Treap{
	int root,tot;
	int lson[N],rson[N],val[N],key[N],sz[N];
	#define ls lson[p]
	#define rs rson[p]
	inline void push_up(int p){
		sz[p]=sz[ls]+sz[rs]+1;
	}
	inline int newnode(int v){
		return ++tot,val[tot]=v,key[tot]=rnd(),sz[tot]=1,tot;
	}
	void split(int p,int v,int &x,int &y){
		if(!p)return x=y=0,void();
		if(val[p]<=v)split(rs,v,rson[x=p],y);
		else split(ls,v,x,lson[y=p]);
		push_up(p);
	}
	int merge(int x,int y){
		if(!x||!y)return x|y;
		if(key[x]<key[y])
			return lson[y]=merge(x,lson[y]),push_up(y),y;
		return rson[x]=merge(rson[x],y),push_up(x),x;
	}
	void insert(int v){
		int x=0,y=0;
		split(root,v-1,x,y),root=merge(merge(x,newnode(v)),y);
	}
	void del(int v){
		int x=0,y=0,z=0;
		split(root,v,x,z),split(x,v-1,x,y);
		root=merge(merge(x,y=merge(lson[y],rson[y])),z);
	}
	int kth(int k){
		int p=root;
		while(1)
			if(k<=sz[ls])p=ls;
			else if(k==sz[ls]+1)return val[p];
			else k-=sz[ls]+1,p=rs;
	}
	int pre(int v){
		int p=root,ans=0;
		while(1)
			if(!p)return ans;
			else if(v<=val[p])p=ls;
			else ans=val[p],p=rs;
	}
	int suf(int v){
		int p=root,ans=0;
		while(1)
			if(!p)return ans;
			else if(v>=val[p])p=rs;
			else ans=val[p],p=ls;
	}
	int rnk(int v){
		int x=0,y=0,ans=0;
		split(root,v-1,x,y),ans=sz[x]+1;
		return root=merge(x,y),ans;
	}
}
using FHQ_Treap::insert;
using FHQ_Treap::del;
using FHQ_Treap::rnk;
using FHQ_Treap::kth;
using FHQ_Treap::suf;
using FHQ_Treap::pre;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1,x;i<=n;i++)cin>>x,insert(x);
	int lst=0,ans=0;
	while(m--){
		int op,x;cin>>op>>x,x^=lst;
		if(op==1)insert(x);
		if(op==2)del(x);
		if(op==3)ans^=(lst=rnk(x));
		if(op==4)ans^=(lst=kth(x));
		if(op==5)ans^=(lst=pre(x));
		if(op==6)ans^=(lst=suf(x));
	}cout<<ans;
}