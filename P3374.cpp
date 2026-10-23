#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,a[N];
int tr[N];
inline int lowbit(int x){return x&-x;}
inline void update(int x,int k){
	while(x<=n)tr[x]+=k,x+=lowbit(x);
}
inline int query(int x,int s=0){
	while(x)s+=tr[x],x-=lowbit(x);
	return s;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int m;cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i],a[i]+=a[i-1];
	while(m--){
		int op,x,y;cin>>op>>x>>y;
		if(op==1)update(x,y);
		else cout<<query(y)-query(x-1)+a[y]-a[x-1]<<"\n";
	}
}