#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m;
int a[N];
char s[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
    int ans=0;
    for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=1;i<=n;i++)cin>>a[i],ans+=a[i];
    s[0]=s[n];
	for(int i=0;i<n;i++)
		if(s[i]=='R'&&s[i+1]=='L'){
            int l=i-1,r=i+2;
            if(l<1)l+=n;
            if(r>n)r-=n;
			int sl=0,sr=0;
			while(l>=1&&s[l]=='R'){
				sl+=a[l],l--;
				if(l<0)l+=n;
			}
			while(r<=n&&s[r]=='L'){
				sr+=a[r],r++;
				if(r>n)r-=n;
			} 
			ans-=min(sl,m)+min(sr,m);
		}
	cout<<ans;
	return 0;
}