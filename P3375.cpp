#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int nxt[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	string a,b;cin>>a>>b;
	int n=a.size(),m=b.size();
	a=" "+a,b=" "+b;
	int now=0;
	for(int i=2;i<=m;i++){
		while(now&&b[now+1]!=b[i])
			now=nxt[now];
		if(b[now+1]==b[i])now++;
		nxt[i]=now;
	}
	now=0;
	for(int i=1;i<=n;i++){
		while(now&&b[now+1]!=a[i])now=nxt[now];
		if(b[now+1]==a[i])now++;
		if(now==m)cout<<i-m+1<<"\n",now=nxt[now];
	}
	for(int i=1;i<=m;i++)
		cout<<nxt[i]<<" ";
}