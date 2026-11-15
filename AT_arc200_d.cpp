#include<bits/stdc++.h>
using namespace std;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	while(T--){
		int m,k;cin>>m>>k;
		if(k%2){
			cout<<"Yes\n"<<k/2+1<<"\n";
			for(int i=0;i<=k/2;i++)cout<<i<<" ";
			cout<<"\n";
		}
		else if(k==m){
			cout<<"Yes\n"<<m<<"\n";
			for(int i=0;i<m;i++)cout<<i<<" ";
			cout<<"\n";
		}
		else if(k==2){
			if(m%2)cout<<"No\n";
			else cout<<"Yes\n2\n0 "<<m/2<<"\n";
		}
		else if(k/2>=3){
			cout<<"Yes\n"<<k/2<<"\n";
			cout<<"0 ";
			for(int i=2;i<=k/2;i++)cout<<i<<" ";
			cout<<"\n";
		}
		else{
			if(m%4)cout<<"No\n";
			else cout<<"Yes\n3\n0 "<<m/2<<" "<<m/4<<"\n";
		}
	}
}