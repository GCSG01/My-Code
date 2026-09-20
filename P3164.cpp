#include<bits/stdc++.h>
using namespace std;
const int N=51;
int n,m;
bitset<N*N>a[N*N];
int ans[N*N];
void gauss(int n){
	for (int i=1;i<=n;i++){
		for(int j=i;j<=n;j++)
			if(a[j][i]>0){
				swap(a[i],a[j]);break;
			}
		if(!a[i][i])ans[i]=1;
		for(int j=i+1;j<=n;j++)
			if(a[j][i])a[j]^=a[i];
	}
	for(int i=n;i>=1;i--)
		for(int j=i+1;j<=n;j++)
			ans[i]^=(ans[j]*a[i][j]); 
}
int get(int i,int j){
    return (i-1)*m+j;
}
int pdx[]={1,0,-1,0,0};
int pdy[]={0,1,0,-1,0};
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            for(int k=0;k<=4;k++){
                int x=i+pdx[k],y=j+pdy[k];
                if(x<1||x>n||y<1||y>m)continue;
                a[get(i,j)][get(x,y)]=1;
            }
    gauss(n*m);
    for(int i=1;i<=n;i++,cout<<"\n")
        for(int j=1;j<=m;j++)
            cout<<ans[get(i,j)]<<" ";
}