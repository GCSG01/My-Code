#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1e9+5,N=2e4+5;
int d[N],c[N],s[N],w[N],dp[N],L[N],R[N];
int n;
struct Segment{
	int lzy[N<<2],w[N<<2];
    #define ls p<<1
    #define rs p<<1|1
	void pushup(int p){
		w[p]=min(w[ls],w[rs]);
        return ;
	}
	void build(int p=1,int l=1,int r=n){
		lzy[p]=0;
		if(l==r)
            return w[p]=dp[l],void();
		int mid=(l+r)/2;
		build(ls,l,mid),build(rs,mid+1,r);
		pushup(p);
        return ;
	}
	void maketag(int p,int x){
		lzy[p]+=x,w[p]+=x;
        return ;
	}
	void pushdown(int p){
		maketag(ls,lzy[p]);
		maketag(rs,lzy[p]);
		lzy[p]=0;
        return ;
	}
	void update(int l,int r,int x,int p=1,int L=1,int R=n){
        if(r<L||R<l)return ;
		if(l<=L&&R<=r)
			return maketag(p,x);
		pushdown(p);
		int mid=(L+R)/2;
		update(l,r,x,ls,L,mid);
		update(l,r,x,rs,mid+1,R);
		pushup(p);
        return ;
	}
	int query(int l,int r,int p=1,int L=1,int R=n){
		if(r<L||R<l)return inf;
		if(l<=L&&R<=r)return w[p];
		pushdown(p);
		int mid=(L+R)/2;
		return min(query(l,r,ls,L,mid),query(l,r,rs,mid+1,R));
	}
}tr,seg;
vector<int>vc[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
	int k,ans=0,sum=0;
	cin>>n>>k;
	for(int i=2;i<=n;i++)cin>>d[i];
	for(int i=1;i<=n;i++)cin>>c[i];
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=1;i<=n;i++)cin>>w[i];
	n++,k++;
	d[n]=w[n]=inf;s[n]=c[n]=0;
	for(int i=1;i<=n;i++){
		L[i]=lower_bound(d+1,d+1+n,d[i]-s[i])-d;
		R[i]=lower_bound(d+1,d+1+n,d[i]+s[i])-d;
		if(d[R[i]]>d[i]+s[i])
            R[i]--;
		vc[R[i]].push_back(i);
	}
	tr.build();
	for(int i=1;i<=n;i++){
		dp[i]=sum+c[i];
		tr.update(1,L[i]-1,w[i]);
		tr.update(R[i]+1,n,w[i]);
		for(auto v:vc[i])
            sum+=w[v];
	}
	ans=dp[n];
	for(int j=2;j<=k;j++){
		tr.build();
		for(int i=1;i<=n;i++){
			if(i!=1)
                dp[i]=tr.query(1,i-1)+c[i];
			else dp[1]=inf;
			for(auto v:vc[i])
				if(L[v]>1)
                    tr.update(1,L[v]-1,w[v]);
		}
		ans=min(ans,dp[n]);
	}
	cout<<ans;
	return 0;
}