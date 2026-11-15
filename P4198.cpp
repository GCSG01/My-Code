#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m;
namespace Tree{
	int tr[N<<2];
	double mx[N<<2];
	#define ls p<<1
	#define rs p<<1|1
	#define mid ((l+r)>>1)
	int get(int l,int r,int p,double k){
		if(mx[p]<=k)return 0;
		if(l==r)return mx[p]>k;
		if(mx[ls]<=k)return get(mid+1,r,rs,k);
		return get(l,mid,ls,k)+tr[p]-tr[ls];
	}
	inline void push_up(int l,int r,int p){
		mx[p]=max(mx[ls],mx[rs]),tr[p]=tr[ls]+get(mid+1,r,rs,mx[ls]);
	}
	void update(int l,int r,int p,int x,double k){
		if(l==r)return mx[p]=k,tr[p]=1,void();
		if(x<=mid)update(l,mid,ls,x,k);
		if(x>mid)update(mid+1,r,rs,x,k);
		push_up(l,r,p);
	}
}
using Tree::update;
using Tree::tr;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	while(m--){
		int x,y;cin>>x>>y;
		update(1,n,1,x,y*1.0/x);
		cout<<tr[1]<<"\n";
	}
}