#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+5;
int n,d,x[N];
int lmx[N],rmx[N];
int cntl[N],cntr[N];
int pre[N],suf[N];
inline void print(int *a){
	for(int i=1;i<=n;i++)cout<<a[i]<<" ";
	cout<<"\n";
}
void solve(){
	cin>>n>>d;
	for(int i=1;i<=n;i++)cin>>x[i],cntl[i]=cntr[i]=pre[i]=suf[i]=0;
	sort(x+1,x+n+1);
	int pos=1;
	for(int i=1;i<=n;i++){
		while(pos<n&&x[pos+1]-x[i]<=d)pos++;
		if(pos!=i)cntr[pos]++;
		rmx[i]=pos;
	}pos=n;
	for(int i=n;i>=1;i--){
		while(pos>1&&x[i]-x[pos-1]<=d)pos--;
		if(pos!=i)cntl[pos]++;
		lmx[i]=pos;
	}
	for(int i=1;i<=n;i++){
		if(rmx[i]!=i)pre[rmx[i]]++;
		if(lmx[i]!=i)suf[lmx[i]]++;
	}
	for(int i=1;i<=n;i++)
		if(lmx[i]!=i&&rmx[lmx[i]]==i)
			pre[i]+=pre[lmx[i]];
	for(int i=n;i>=1;i--)
		if(rmx[i]!=i&&lmx[rmx[i]]==i)
			suf[i]+=suf[rmx[i]];
	int ans=0;
	for(int i=1;i<n;i++){
		int lsum=cntr[i+1],rsum=cntl[i];
		if(lmx[i+1]==i)rsum--;
		if(rmx[i]==i+1)lsum--;
		if(lmx[rmx[i+1]]==i)
			rsum+=suf[rmx[i+1]];
		if(rmx[lmx[i]]==i+1)
			lsum+=pre[lmx[i]];
		ans+=lsum*rsum;
	}
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int c,T;cin>>c>>T;
	while(T--)solve();
}
/*
10 3
0 3 6 7 8 9 10 11 14 17

7 666666666666666663
-1000000000000000000
-555555555555555558
-111111111111111116
111111111111111105
333333333333333326
555555555555555547
999999999999999989
*/