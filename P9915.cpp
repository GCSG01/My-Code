#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int qpow(int x,int y,int s=1){
	while(y){
		if(y&1)s*=x,s%=mod;
		x*=x,x%=mod,y>>=1;
	}return s;
}
int n,q;
int get(int x,int y){
	if(y>63)return n;
	x>>=y;
	if(!x)return n;
	int d=x&1;
	x>>=1,y++;
	while((x&1)==d)
		x>>=1,y++;
	return y;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>q;
	while(q--){
		int x,y;cin>>x>>y;
		cout<<(qpow(2,get(x,y))-1+mod)%mod<<"\n";
	}
}