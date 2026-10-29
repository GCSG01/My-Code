#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5,mod=998244353;
struct Segment_Tree {
	int n,sum[N<<2],tag[N<<2];
	Segment_Tree(int size):n(size){}
	#define ls p<<1
	#define rs p<<1|1
	#define mid ((l+r)>>1)
	void upd(int p,int mul){
		sum[p]=1ll*sum[p]*mul%mod;
		tag[p]=1ll*tag[p]*mul%mod;
	}
	void push_down(int p){
		if(tag[p]==1)return ;
		upd(ls,tag[p]),upd(rs,tag[p]),tag[p]=1;
	}
	void update(int p,int l,int r,int ql,int qr,int mul){
		if(ql<=l&&r<=qr)
			return upd(p,mul);
		push_down(p);
		if(ql<=mid)update(ls,l,mid,ql,qr,mul);
		if(qr>mid)update(rs,mid+1,r,ql,qr,mul);
		sum[p]=sum[ls]+sum[rs];
		if(sum[p]>=mod)sum[p]-=mod;
	}
	void add(int p,int l,int r,int x,int v){
		if(l==r)
			return sum[p]+=v,sum[p]%=mod,void();
		push_down(p);
		if(x<=mid)add(ls,l,mid,x,v);
		else add(rs,mid+1,r,x,v);
		sum[p]=sum[ls]+sum[rs];
		if(sum[p]>=mod)sum[p]-=mod;
	}
	int query(int p,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr)return sum[p];
		push_down(p);
		int sum=0;
		if(ql<=mid)sum+=query(ls,l,mid,ql,qr),sum%=mod;
		if(qr>mid)sum+=query(rs,mid+1,r,ql,qr),sum%=mod;
		return sum;
	}
	void update(int l, int r, int mul) {
		if(l<=r)update(1,1,n,l,r,mul);
	}
	int query(int l,int r){
		if(l>r)return 0;
		return query(1,1,n,l,r);
	}
	void add(int x,int v){
		add(1,1,n,x,v);
	}
};
vector<int>pos[N];
int f[N],pw2[N];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n;cin>>n,pw2[0]=1;
	for (int i=1;i<=n;i++)pw2[i]=2ll*pw2[i-1]%mod;
	for(int i=1;i<=n;i++){
		int x;cin>>x;
		if(x<=n)
			pos[x].push_back(i),f[x]++;
	}
	vector<int>cnt(n+1);
	int sum=0;
	for(int i=0;i<=n;i++)
		sum+=f[i],cnt[i]=n-sum;
	Segment_Tree dp(n+1);dp.add(n+1,1);
	int ans=0;
	for(int mex=0;mex<=n;mex++){
		ans=(ans+1ll*dp.sum[1]*pw2[cnt[mex]])%mod;
		if(mex==n||pos[mex].empty())break;
		int siz=pos[mex].size();
		vector<pair<int,int>>a;
		for(int i:pos[mex])
			a.emplace_back(i,dp.query(i+1,n+1));
		int l=1;
		for(int i=0;i<=siz;i++){
			int r=i<siz?pos[mex][i]-1:n+1;
			dp.update(l,r,(pw2[siz-i]-1+mod)%mod);
			if(i<siz)l=pos[mex][i];
		}
		for(auto [p,cnt]:a)dp.add(p,cnt);
	}
	cout<<ans;
}