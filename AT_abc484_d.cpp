#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,t[N],a[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	int ans=1;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]!=a[i-1])ans+=i-1-t[a[i]];
		t[a[i]]++;
	}
	cout<<ans;
}