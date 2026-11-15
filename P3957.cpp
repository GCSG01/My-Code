#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5,inf=1e18;
int n,d,k;
int x[N],s[N],f[N],q[N];
bool check(int L,int R){
    fill(f+1,f+n+1,-inf);
    memset(q,0,sizeof(q));
	int l=1,r=0,j=0;
	f[0]=0;
    for(int i=1;i<=n;i++){
    	while(x[i]-x[j]>=L&&j<i){
    		if(f[j]>-inf){
    			while(f[q[r]]<=f[j]&&l<=r)r--;
    			q[++r]=j;
			}
    		j++;
		}
    	while(x[i]-x[q[l]]>R&&l<=r)l++;
    	if(l<=r)f[i]=f[q[l]]+s[i];
    	if(f[i]>=k)return true;
	}
    return false;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>d>>k;
    for(int i=1;i<=n;i++)cin>>x[i]>>s[i];
    int l=0,r=1e9,ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(max(1ll,d-mid),d+mid))ans=mid,r=mid-1;
        else l=mid+1;
    }cout<<ans;
}