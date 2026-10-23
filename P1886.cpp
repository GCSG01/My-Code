#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,k,a[N];
int q[N],l=1,r;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		while(l<=r&&a[q[r]]>=a[i])r--;
		q[++r]=i;
		while(l<r&&i-q[l]+1>k)l++;
		if(i>=k)cout<<a[q[l]]<<" ";
	}
	l=1,r=0,cout<<"\n";
	for(int i=1;i<=n;i++){
		while(l<=r&&a[q[r]]<=a[i])r--;
		q[++r]=i;
		while(l<r&&i-q[l]+1>k)l++;
		if(i>=k)cout<<a[q[l]]<<" ";
	}
}