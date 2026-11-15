#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
const int N=1e4+9;
int pdx[]={0,1,0,-1};
int pdy[]={1,0,-1,0};
int n,x[N],y[N];
pair<int,int>a[N];
int dist(pair<int,int>a,pair<int,int>b){
	return abs(a.x-b.x)+abs(a.y-b.y);
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y,x[i]=a[i].x,y[i]=a[i].y;
	sort(x+1,x+n+1),sort(y+1,y+n+1);
	int lx=0,ly=0,rx=0,ry=0;
	if(n%2)lx=rx=x[n/2+1],ly=ry=y[n/2+1];
	else lx=x[n/2],rx=x[n/2+1],ly=y[n/2],ry=y[n/2+1];
	int res=(rx-lx+1)*(ry-ly+1);
	for(int i=1;i<=n;i++)
		if(a[i].x>=lx&&a[i].x<=rx&&a[i].y>=ly&&a[i].y<=ry)
			res--;
	int dis=0;
	for(int i=1;i<=n;i++)
		dis+=dist(a[i],{lx,ly});
	if(res==0){
		int mn=1e18,cnt=0;
		for(int i=0;i<4;i++){
			int nx=lx+pdx[i],ny=ly+pdy[i];
			dis=0;
			for(int i=1;i<=n;i++)
				dis+=dist(a[i],{nx,ny});
			if(mn>dis)mn=dis,cnt=1;
			else if(mn==dis)cnt++;
		}
		return cout<<mn<<" "<<cnt,0;
	}
	cout<<dis<<" "<<res;
}