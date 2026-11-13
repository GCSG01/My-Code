#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,inf=1e9;
int n,q,a[N],b[N],p[N];
map<int,int>t;
namespace Segment_Tree{
	struct matrix{
		int a[3][3];
		matrix(){
			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
					a[i][j]=inf;
		}
		matrix operator*(const matrix &v)const{
			matrix c;
			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
					c.a[i][j]=min({a[i][0]+v.a[0][j],a[i][1]+v.a[1][j],a[i][2]+v.a[2][j],inf});
			return c;
		}
	}tr[N<<2];
	#define ls p<<1
	#define rs p<<1|1
	#define mid ((l+r)>>1)
	matrix get(int x){
		matrix res;
		if(!b[x]){
			res.a[0][0]=0;
			if(x==1||b[x-1])
				res.a[1][1]=res.a[2][2]=0;
		}
		else{
			res.a[0][0]=1;
			if(b[x]==1)
				res.a[0][1]=0,res.a[2][0]=1;
			else res.a[0][2]=0,res.a[1][0]=1;
		}
		return res;
	}
	void build(int l,int r,int p){
		if(l==r)
			return tr[p]=get(l),void();
		build(l,mid,ls),build(mid+1,r,rs),tr[p]=tr[ls]*tr[rs];
	}
	void update(int l,int r,int p,int x){
		if(l==r)
			return tr[p]=get(l),void();
		if(x<=mid)update(l,mid,ls,x);
		else update(mid+1,r,rs,x);
		tr[p]=tr[ls]*tr[rs];
	}
}
using Segment_Tree::build;
using Segment_Tree::update;
using Segment_Tree::tr;
int main(){
	// freopen("middle.in","r",stdin);
	// freopen("middle.out","w",stdout);
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	while(T--){
		cin>>n>>q,t.clear();
		for(int i=1;i<=n;i++)
			cin>>a[i],b[i]=1,p[i]=i;
		for(int i=1;i+2<=n;i++){
			int x=a[i],y=a[i+1],z=a[i+2];
			t[max(min(x,y),min(max(x,y),z))]=0;
		}
		sort(p+1,p+n+1,[](int A,int B){return a[A]<a[B];});
		build(1,n,1);
		int l=1;
		while(l<=n){
			int r=l;
			while(r<n&&a[p[r+1]]==a[p[l]])r++;
			for(int i=l;i<=r;i++)b[p[i]]=0;
			for(int i=l;i<=r;i++)update(1,n,1,p[i]);
			if(t.count(a[p[l]]))
				t[a[p[l]]]=tr[1].a[0][0];
			for(int i=l;i<=r;i++)b[p[i]]=-1;
			for(int i=l;i<=r;i++)update(1,n,1,p[i]);
			l=r+1;
		}
		while(q--){
			int k;cin>>k;
			if(t.count(k))cout<<t[k]<<"\n";
			else cout<<"-1\n";
		}
	}
}