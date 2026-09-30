#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=80;
int n,m;
int p[N],a[N];
void add(int x){
	for(int i=62;i>=0;i--){
		if(!((x>>i)&1))continue;
		if(!p[i]){
			p[i]=x;break;
		}
		x^=p[i];
	}
	return ;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		string s;cin>>s;
		int cnt=0;
		for(int j=0;j<n;j++)
			if(s[j]=='O')cnt^=(1ll<<j);
		add(cnt);
	}
	int ans=0;
	for(int i=0;i<=62;i++)
		if(p[i])ans++;
	cout<<(1ll<<ans)%2008;
	return 0;
}