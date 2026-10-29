#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
unordered_map<int,bool>f;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	while(T--){
		int n,m,x,ans=0;cin>>n,m=n*2,f.clear();
		while(m--)cin>>x,f[x]=1;
		if(f.size()>n)cout<<"Kevin\n";
		else cout<<"Qingyu\n";
	}
}