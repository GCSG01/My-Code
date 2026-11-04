#include<bits/stdc++.h>
// #define int long long
using namespace std;
const int N=3e6+5;
int n,p;
int inv[N];
int sum[N];
int qpow(int x,int y,int s=1){
	for(;y;x=1ll*x*x%p,y>>=1)
		if(y&1)s=1ll*s*x%p;
	return s;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>p,sum[0]=1;
	for(int i=1;i<=n;i++)sum[i]=1ll*sum[i-1]*i%p;
	int now=qpow(sum[n],p-2);
	for(int i=n;i>=1;i--)
		inv[i]=1ll*now*sum[i-1]%p,now=1ll*now*i%p;
	for(int i=1;i<=n;i++)cout<<inv[i]<<"\n";
}