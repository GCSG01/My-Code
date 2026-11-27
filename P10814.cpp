#include<bits/stdc++.h>
// #define int long long
using namespace std;
constexpr int N=4e6+5;
int n,m,a[N];
int Ans[N];
array<int,4>e[N];
int tr[N];
inline int lowbit(int x){return x&-x;}
inline void update(int x){
	while(x<=2000000)tr[x]++,x+=lowbit(x);
}
inline int query(int x){
	int s=0;
	while(x)s+=tr[x],s-=lowbit(x);
	return s;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1,l,r,x;i<=m;i++)
		cin>>l>>r>>x,e[i]={l-1,x,i,-1},e[n+i]={r,x,i,1};
	sort(e+1,e+m+1,[](auto A,auto B){
		return A[0]==B[0]?A[1]<B[1]:A[0]<B[0];
	});
	int now=0;
	for(int i=1;i<=m;i++){
		while(now<e[i][0])update(a[++now]);
		Ans[e[i][2]]=e[i][3]*query(e[i][1]);
	}
	for(int i=1;i<=m;i++)cout<<Ans[i]<<"\n";
}