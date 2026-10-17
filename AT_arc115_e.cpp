#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5,mod=998244353;
int n,a[N];
int f[N][2],sum[N][2];
stack<int>st;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	f[0][0]=sum[0][0]=1;
	for(int i=1;i<=n;i++){
		while(!st.empty()&&a[st.top()]>=a[i])st.pop();
		if(st.empty())
			for(int x=0;x<=1;x++)
				f[i][x]=sum[i-1][x^1]*a[i]%mod;
		else for(int x=0;x<=1;x++)
			f[i][x]=(f[st.top()][x]+(sum[i-1][x^1]-sum[st.top()-1][x^1])*a[i]%mod)%mod;
		st.push(i);
		sum[i][0]=(sum[i-1][0]+f[i][0])%mod;
		sum[i][1]=(sum[i-1][1]+f[i][1])%mod;
	}
	int ans=f[n][0]-f[n][1];
	if(n&1)ans*=-1;
	cout<<(ans%mod+mod)%mod;
}