#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+5;
struct node{
	int l,r;
	mutable int w;
	inline node(int L,int R=0,int w=0):l(L),r(R),w(w){}
	inline bool operator<(const node& b)const{return l<b.l;}
};
set<node>s;
inline set<node>::iterator split(int pos){
	auto ii=s.lower_bound(node(pos));
	if(ii!=s.end()&&ii->l==pos)return ii;ii--;
	int l,r,w;l=ii->l,r=ii->r,w=ii->w;
	s.erase(ii);
	s.insert(node(l,pos-1,w));
	return s.insert(node(pos,r,w)).X;
}
struct ask{
	int l,r,t,i;
	inline bool operator<(const ask&b)const{
		return t<b.t;
	}	
};
vector<ask>v;
const int MAXN=1e5+10;
int a[MAXN],lim[MAXN],c[MAXN];
pair<int,int> op[MAXN];
ll ans[MAXN];
inline void baoli(int l,int r,int t,int id)
{
	for(int i=l;i<=r;i++)ans[id]+=min((ll)lim[i],(ll)a[i]+(ll)c[i]*t);	
}
struct BIT
{
	ll t[MAXN];
	inline void add(int x,ll k)
	{
		for(;x<MAXN;x+=x&-x)t[x]+=k;
	}
	inline ll ask(int x)
	{
		ll ans=0;
		for(;x;x-=x&-x)ans+=t[x];
		return ans;
	}
	inline ll ask(int ii,int it){return ask(it)-ask(ii-1);}
}t[2];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n;cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>lim[i]>>c[i];
		if(c[i])op[i]={(lim[i]+c[i]-1)/c[i],i};
		else op[i]={(int)1e9,i};
	}
	s.insert(node(1,n,-1));
	sort(op+1,op+n+1);
	int m;cin>>m;
	for(int i=1;i<=m;i++){
		int l,r,t;
		cin>>t>>l>>r;
		auto rr=split(r+1),L=split(l);
		for(auto ii=L;ii!=rr;ii++)
			if(ii->w>=0) v.push_back({ii->l,ii->r,t-ii->w,i});
			else baoli(ii->l,ii->r,t,i);
		s.erase(L,rr);
		s.insert(node(l,r,t));
	}
	sort(v.begin(),v.end());
	for(int i=1;i<=n;i++) t[0].add(i,c[i]);
	int j=1;
	for(auto&p:v){
		cmin(p.t,100000);
		while(j<=n&&op[j].X<=p.t){
			t[0].add(op[j].Y,-c[op[j].Y]);
			t[1].add(op[j].Y,lim[op[j].Y]);
			j++;
		}
		ans[p.i]+=t[0].ask(p.l,p.r)*p.t+t[1].ask(p.l,p.r);
	}
	for(int i=1;i<=m;i++)cout<<ans[i]<<'\n';
	return 0;
} 