#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,m,a[N],b[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=m;i++)cin>>b[i];
		int pos=0;
		for(int i=1;i<=n;i++)
			if(a[i]==b[pos+1])pos++;
		if(pos>=m)cout<<"Yes\n";
		else cout<<"No\n";
	}
}