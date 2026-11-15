#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5,mod=1e9+7;
int n,f[N];
int s[N];
struct node{
	int l,r;
}a[N];
int qpow(int x,int y,int s=1){
	for(;y;x*=x,x%=mod,y>>=1)
		if(y&1)s*=x,s%=mod;
	return s;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].l>>a[i].r,s[a[i].r]++;
	sort(a+1,a+n+1,[](node A,node B){return A.l<B.l;});
	for(int i=1;i<=2*n;i++)s[i]+=s[i-1];
	for(int i=1;i<=n;i++)
		f[i]=(2*f[i-1]+qpow(2,s[a[i].l]))%mod;
	cout<<f[n];
}