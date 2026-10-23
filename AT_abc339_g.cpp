#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int a[N],n;
int B[N],bk;
int id[N],ll[N],rr[N];
int sum[N];
int solve(int l,int r,int x){
	int L=id[l],R=id[r],ans=0;
	if(L==R){
		for(int i=l;i<=r;i++)
			if(a[i]<=x)ans+=a[i];
		return ans;
	}
	for(int i=l;i<=rr[L];i++)
		if(a[i]<=x)ans+=a[i];
	for(int i=ll[R];i<=r;i++)
		if(a[i]<=x)ans+=a[i];
	for(int i=L+1;i<R;i++){
		if(B[ll[i]]>x)continue;
		int pos=upper_bound(B+ll[i],B+rr[i]+1,x)-B-1;
		ans+=sum[pos]-sum[ll[i]-1];
		// cout<<ll[i]<<" "<<rr[i]<<" "<<pos<<" "<<sum[pos]<<" "<<sum[ll[i]-1]<<" "<<ans<<"\n";
	}return ans;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n,bk=min(2000ll,n);
	for(int i=1;i<=n;i++)cin>>a[i],B[i]=a[i];
	for(int i=1;i<=n;i++)id[i]=i/bk+1,rr[id[i]]=i;
	for(int i=1;i<=n;i++)
		if(!ll[id[i]])
			ll[id[i]]=i;
	for(int i=1;i<=n/bk+1;i++)
		sort(B+ll[i],B+rr[i]+1);
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+B[i];
	int q,lst=0;cin>>q;
	while(q--){
		int l,r,x;cin>>l>>r>>x,l^=lst,r^=lst,x^=lst;
		cout<<(lst=solve(l,r,x))<<"\n";
	}
}