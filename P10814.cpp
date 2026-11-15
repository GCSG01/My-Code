#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
	char c=getchar_unlocked();x=0;
	while(c<'0'||c>'9')c=getchar_unlocked();
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar_unlocked();
}
const int N=2e6+5;
int g[N],ans[N];
int n,m;
struct node{
	int y,id,op;
};
vector<node>p[N];
int tr[N];
inline int lowbit(int x){return x&-x;}
void add(int x){
	while(x<=N-5)tr[x]++,x+=lowbit(x);
}
int query(int x,int s=0){
	while(x)s+=tr[x],x-=lowbit(x);
	return s;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	rd(n),rd(m);
	for(int i=1;i<=n;i++)rd(g[i]);
	for(int i=1,l,r,x;i<=m;i++)
		rd(l),rd(r),rd(x),p[l-1].push_back({x,i,-1}),p[r].push_back({x,i,1});
	for(int i=1;i<=n;i++){
		add(g[i]);
		for(auto j:p[i])
			ans[j.id]+=query(j.y)*j.op;
	}
	for(int i=1;i<=m;i++)cout<<ans[i]<<"\n";
}