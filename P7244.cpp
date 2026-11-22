#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5,inf=1e9;
int n,k,a[N];
int st[N],top;
int val[N],mx[N];
int f[N];
bool check(int d){
	top=0;
	memset(mx,-0x3f,sizeof mx);
	memset(val,0,sizeof val);
	memset(f,0,sizeof f);
	for(int i=1;i<=n;i++){
		int mxx=-inf;
		while(a[st[top]]<a[i]&&top>0)
			mxx=max(mxx,val[top--]);
		st[++top]=i,val[top]=max(mxx,f[i-1]+1);
		mx[top]=mx[top-1];
		if(a[st[top]]%d==0)
			mx[top]=max(mx[top],val[top]);
		f[i]=mx[top];
	}
	return f[n]>=k;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>k;
	int mx=0;
	for(int i=1;i<=n;i++)cin>>a[i],mx=max(mx,a[i]);
	int ans=0;
	for(int i=mx;i>=1;i--)
		if(mx%i==0&&check(i))
			return cout<<i,0;
}