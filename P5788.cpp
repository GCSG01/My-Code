#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e6+5;
int n,a[N],f[N];
int st[N],top;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=n;i>=1;i--){
		while(top&&a[st[top]]<=a[i])top--;
		f[i]=st[top];
		st[++top]=i;
	}
	for(int i=1;i<=n;i++)cout<<f[i]<<" ";
}