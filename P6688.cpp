#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5,mod=998244353;
int a[N];
int n,m;
namespace Tree{
	int tree[N<<2],minn[N<<2];
	inline int ls(int p){return p<<1;}
	inline int rs(int p){return p<<1|1;}
	void push_up(int p){
		tree[p]=tree[ls(p)]+tree[rs(p)];
		tree[p]%=mod;
		minn[p]=min(minn[ls(p)],minn[rs(p)]);
	}
	void build(int l,int r,int p){
		if(l==r)
			return tree[p]=a[l]*a[l]%mod,minn[p]=a[l],void();
		int mid=(l+r)>>1;
		build(l,mid,ls(p)),build(mid+1,r,rs(p));
		return push_up(p);
	}
	int query_sum(int l,int r,int ll,int rr,int p){
		if(ll<=l&&r<=rr)return tree[p];
		int mid=(l+r)>>1,s=0;
		if(ll<=mid)s+=query_sum(l,mid,ll,rr,ls(p));
		if(rr>mid)s+=query_sum(mid+1,r,ll,rr,rs(p));
		return s%mod;
	}
	int query_min(int l,int r,int ll,int rr,int p){
		if(ll<=l&&r<=rr)return minn[p];
		int mid=(l+r)>>1,s=INT_MAX;
		if(ll<=mid)s=min(s,query_min(l,mid,ll,rr,ls(p)));
		if(rr>mid)s=min(s,query_min(mid+1,r,ll,rr,rs(p)));
		return s;
	}
	void update(int l,int r,int x,int v,int p){
		if(l==r)
			return tree[p]=v*v%mod,minn[p]=v,void();
		int mid=(l+r)>>1;
		if(x<=mid)update(l,mid,x,v,ls(p));
		else update(mid+1,r,x,v,rs(p));
		push_up(p);
		return ;
	}
}
using Tree::build;
using Tree::update;
using Tree::query_sum;
using Tree::query_min;
int qpow(int x,int y){
    int s=1;
    while(y){
        if(y&1)s*=x,s%=mod;
        x*=x,x%=mod,y>>=1;
    }
    return s;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	Tree::build(1,n,1);
	int ans=0;
	while(m--){
		int op,l,r,k;
		cin>>op>>l>>r;
		if(op==1)
			cin>>l>>r,l^=ans,r^=ans,Tree::update(1,n,l,r,1);
		else{
			cin>>k,l^=ans,r^=ans,k^=ans;
			int x=Tree::query_min(1,n,l,r,1);
			int y=Tree::query_sum(1,n,l,r,1);
			int len=r-l+1,cnt=len*x%mod*x%mod;
			cnt+=x*k%mod*len%mod*(len-1)%mod;
			cnt%=mod,len--;
			int sum=k*k%mod*len%mod*(len+1)%mod*(len*2+1)%mod*qpow(6,mod-2)%mod;
			if((cnt+sum)%mod==y)cout<<"Yes\n",ans++;
			else cout<<"No\n";
		}
	}
	return 0;
}