#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,k;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j+k-1<=n-i+1;j++)
			cout<<j<<" "<<j+k-1<<"\n";
}