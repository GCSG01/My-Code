#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,m,a[N],b[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	while(T--){
		cin>>n>>m,a[0]=0,a[n+1]=m;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)cin>>b[i];
		sort(b+1,b+n+1);
		for(int i=2;i<=n;i++)b[i]+=b[i-1];
		priority_queue<int>q;
		int r=n,ans=0;
		while(b[r]>=m)r--;
		for(int i=n;i>=0;i--){
			int l=r;
			while(l>=1)
				if(a[i]<=b[l]&&b[l]<a[i+1])l--;
				else break;
			l++;
			if(l>r){
				q.push(a[i+1]-a[i]);continue;
			}
			for(int j=r;j>l;j--)
				if(!q.empty())
					ans+=q.top(),q.pop();
			if(!q.empty()&&q.top()>=a[i+1]-b[l])
				ans+=q.top(),q.pop(),q.push(a[i+1]-a[i]);
			else{
				int cnt=b[l]-a[i];
				if(!q.empty())cnt+=q.top(),q.pop();
				ans+=a[i+1]-b[l],q.push(cnt);
			}
			r=l-1;
			if(r<1)break;
		}
		cout<<ans<<"\n";
	}
}