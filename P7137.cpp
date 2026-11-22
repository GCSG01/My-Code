#include<bits/stdc++.h>
using namespace std;
const int N=2.5e3+5;
int n,m,a[N];
double f[N][N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1,[](int A,int B){return A>B;});
	double sum=0;
	for(int i=1;i<=n;i++){
		sum+=a[i];
		for(int j=1;j<=min(i,m);j++)
			if(i==j)f[i][j]=sum/2;
			else f[i][j]=max(f[i-1][j],(f[i-1][j]+f[i-1][j-1]+a[i])/2.0);
	}
	printf("%.6lf",sum-f[n][m]);
}