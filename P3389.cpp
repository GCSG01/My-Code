#include<bits/stdc++.h>
using namespace std;
const int N=3e2+5;
const double eps=1e-10;
double a[N][N],ans[N];
int n;
void print(){
	for(int i=1;i<=n;i++,cout<<"\n")
		for(int j=1;j<=n+1;j++)
			cout<<a[i][j]<<" ";
}
void guass(){
	for(int i=1;i<=n;i++){
		int pos=i;
		for(;pos<=n;pos++)
			if(fabs(a[pos][i])>eps)
				break;
		if(pos>n)cout<<"No Solution",exit(0);
		for(int j=1;j<=n+1;j++)
			swap(a[i][j],a[pos][j]);
		for(int j=1;j<=n;j++)
			if(j!=i&&fabs(a[j][i])>eps){
				double d=a[j][i]/a[i][i];
				for(int k=i;k<=n+1;k++)
					a[j][k]-=d*a[i][k];
			}
	}
	for(int i=1;i<=n;i++)
		if(fabs(a[i][i])<eps)cout<<"No Solution",exit(0);
		else ans[i]=a[i][n+1]/a[i][i];
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++)
			cin>>a[i][j];
	guass();
	for(int i=1;i<=n;i++)
		printf("%.2lf\n",ans[i]);
}