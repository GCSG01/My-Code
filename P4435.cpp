#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,q,a[N];
struct node{
	int l,r,w;
};
struct tree{
	int ans;
	vector<node>f,t;
}tr[N<<2];
inline int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}
vector<node> merge(vector<node> x,vector<node> y){
	vector<node>ans;
    for(auto i:x)ans.push_back(i);
	for(int i=0;i<y.size();i++){
		int sum=gcd(x[x.size()-1].w,y[i].w);
        node &b=ans[ans.size()-1];
		if(sum==b.w)
            b.l=min(b.l,y[i].l),b.r=max(b.r,y[i].r);
		else ans.push_back({y[i].l,y[i].r,sum});
	}
	return ans;
}
#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
tree push_up(tree x,tree y){
	tree ans;ans.ans=0;
	ans.f=merge(x.f,y.f);
	ans.t=merge(y.t,x.t);
	int len=x.t.size()-1,lim=y.f.size()-1;
	for(int l=len,r=0;l>=0;l--){
		while(r<=lim&&gcd(y.f[r].w,x.t[l].w)!=1)r++;r--;
		if(r>=0)ans.ans+=(x.t[l].r-x.t[l].l+1)*(y.f[r].r-y.f[0].l+1);
		else r++;
	}
	ans.ans+=x.ans+y.ans;
	return ans;
}
void build(int p,int l,int r){
	if(l==r){
		tr[p].f.push_back({l,r,a[l]});
		tr[p].t.push_back({l,r,a[l]});
		if(a[l]!=1)tr[p].ans=1;
		else tr[p].ans=0;
		return ;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	tr[p]=push_up(tr[ls],tr[rs]);
}
void update(int p,int l,int r,int x,int sum){
	if(l==r){
		vector<node> v;v.push_back({l,r,sum});
		tr[p].f=v;tr[p].t=v;
		if(sum!=1)tr[p].ans=1;
		else tr[p].ans=0;
		return;
	}
	if(mid>=x)update(ls,l,mid,x,sum);
	else update(rs,mid+1,r,x,sum);
	tr[p]=push_up(tr[ls],tr[rs]);
}
tree query(int p,int l,int r,int s,int t){
	if(l>=s&&r<=t)return tr[p];
	if(t<=mid)return query(ls,l,mid,s,t);
	if(s>mid)return query(rs,mid+1,r,s,t);
    return push_up(query(ls,l,mid,s,t),query(rs,mid+1,r,s,t));
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	while(q--){
        int op,x,y;cin>>op>>x>>y;
		if(op==1)update(1,1,n,x,y);
		else cout<<query(1,1,n,x,y).ans<<"\n";
	}
	return 0;
}