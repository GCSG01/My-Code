#include<bits/stdc++.h>
#define double long double
using namespace std;
const int N=4e5+5;
struct node{
	int x,y,xx,yy;
}p[N];
int dis(node A,node B){
	return (A.xx-B.xx)*(A.xx-B.xx)+(A.yy-B.yy)*(A.yy-B.yy);
}
int n;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1,x,y;i<=n;i++)
		cin>>x>>y,p[i]={(int)(x*cos(1.14)-y*sin(1.14)),(int)(x*sin(1.14)+y*cos(1.14)),x,y};
	sort(p+1,p+n+1,[](node A,node B){
		if(A.x<B.x||(A.x==B.x&&A.y<B.y))return 1;
		return 0;
	});
	int ans=0;
	for(int i=1;i<=min(20000,n);i++)
		for(int j=n-min(20000,n)+1;j<=n;j++)
			ans=max(ans,dis(p[i],p[j]));
	cout<<ans;
}