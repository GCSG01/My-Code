#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+5;
double p[N][N];
double r[N],w[N],d[N],g[N];
int n;
void move(double lon){
	memset(d,0,sizeof d);
	memset(w,0,sizeof w);
	for(int i=1;i<=n;i++)
        for(int j=1;j<n;j++)
            d[i]+=(r[j]-p[i][j])*(r[j]-p[i][j]);
    double s=0.0;
	for(int i=1;i<=n;i++)
		d[i]=g[i]=sqrt(d[i]),s+=g[i];
	s/=n;
	for(int i=1;i<=n;i++)g[i]-=s;
    for(int i=1;i<=n;i++)
	    for(int j=1;j<n;j++)
			w[j]+=g[i]*(p[i][j]-r[j])/s;
    s=0;
	for(int i=1;i<n;i++)s+=w[i]*w[i];
	s=sqrt(s);
    if(!s)return;
	for(int i=1;i<n;i++)r[i]+=lon/s*w[i];
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n,n++;
    for(int i=1;i<=n;i++)
        for(int j=1;j<n;j++)
            cin>>p[i][j];
    double lon=4587;
    while(lon>1e-9)
        move(lon),lon*=0.999;
    for(int i=1;i<n;i++)
        printf("%.3f ",r[i]);
}