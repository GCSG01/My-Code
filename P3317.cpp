#include <bits/stdc++.h>
using namespace std;
const int N=50+5;
const double eps=1e-8;
int n;
double ans=1,a[N][N];
double det(){
	for(int i=2;i<n;i++){
		int pos=i;
		for(int j=i+1;j<=n;j++)
            if(fabs(a[j][i])>eps)pos=j;
		swap(a[i],a[pos]);
		if(fabs(a[i][i])<eps)return 0;
		for(int j=i+1;j<=n;j++)
			for(int k=n;k>=i;k--)
				a[j][k]-=a[j][i]/a[i][i]*a[i][k];
	}
	for(int i=2;i<=n;i++)
        ans*=a[i][i];
	return fabs(ans);
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(i!=j){
				if(1-a[i][j]<eps)a[i][j]-=eps;
				if(i<j)ans*=(1-a[i][j]);
				a[i][j]=-a[i][j]/(1-a[i][j]),
                a[i][i]-=a[i][j];
			}
	cout<<det();
}