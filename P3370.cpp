#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int N=5e5+5;
ull a[N];
ull hs(string s){
	ull bas=1,h=0;
	for(int i=0;i<s.size();i++)
		h+=s[i]*bas,bas*=458791;
	return h;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n;cin>>n;
	for(int i=1;i<=n;i++){
		string s;cin>>s;
		a[i]=hs(s);
	}
	sort(a+1,a+n+1);
	int cnt=unique(a+1,a+n+1)-a-1;
	cout<<cnt;
}