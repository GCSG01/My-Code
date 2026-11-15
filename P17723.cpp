#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int N=2e6+5;
int n,a[N];
int t[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n,a[n+1]=(1<<30)-1;
	for(int i=1;i<=n;i++)cin>>a[i];
	int ans=0;
	for(int k=0;k<30;k++){
		int r=0,cnt1=1<<k,cnt2=0;
		memset(t,0,sizeof(t));
		for(int i=1;i<=n;i++){
			if(i>1){
				if(a[i-1]<min(n,(1ull<<k))&&!--t[a[i-1]])cnt1++;
				cnt2-=(a[i-1]>>k)&1;
			}
			while(r<=n&&((cnt1&&!cnt2)||r<i)){
				cnt2+=(a[++r]>>k)&1;
				if(a[r]<min(n,(1ull<<k))&&!t[a[r]]++)cnt1--;
			}
			ans+=(n-r+1)*(1<<k);
		}
	}
	cout<<ans;
}