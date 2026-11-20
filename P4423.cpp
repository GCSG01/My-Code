#include<bits/stdc++.h>
using namespace std;
const int N=2e5+3;
struct node{
	double x,y;
}a[N],b[N];
double dis(int i,int j){
	return hypot(b[i].x-b[j].x,b[i].y-b[j].y);
}
double solve(int l,int r){
	if(l==r)return 1e18;
	int mid=(l+r)>>1,tot=0;
	double p=a[mid].x,res=min(solve(l,mid),solve(mid+1,r)),d=res/2;
	merge(a+l,a+mid+1,a+mid+1,a+r+1,b,[](node a,node b){return a.y<b.y;});
	memcpy(a+l,b,sizeof(node)*(r-l+1));
	for(int i=l;i<=r;i++)
		if(fabs(a[i].x-p)<d)
			b[++tot]=a[i];
	for(int i=1;i<=tot;i++)
		for(int j=i+1;j<=tot&&abs(b[j].y-b[i].y)<d;j++)
			for(int k=j+1;k<=tot&&abs(b[k].y-b[i].y)<d;k++)
				res=min(res,dis(i,j)+dis(j,k)+dis(k,i));
	return res;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n;cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y;
	sort(a+1,a+n+1,[](node a,node b){return a.x<b.x;});
	printf("%.6lf",solve(1,n));
}