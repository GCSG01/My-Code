#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e4+5;
int n;
struct node{
	int x,y;
}a[N];
int fa[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int dis(node A,node B){
	return (A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y);
}
bool check(int X){
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(dis(a[i],a[j])<=X)
				fa[find(i)]=find(j);
	for(int i=2;i<=n;i++)
		if(find(i)!=find(i-1))return false;
	return true;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y;
	int ans=-1,l=0,r=1e18;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans;
}