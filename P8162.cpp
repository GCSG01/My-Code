#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=505;
const double inf=1e18;
double f[N][N];
double s[N][N],x[N];
int tot=0;
struct node{
    double a,b;
}a[N];
int n,k;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i].a>>a[i].b;
    for(int i=1;i<=n;i++)
        if(a[i].b==-1)a[i].b=inf;
    sort(a+1,a+n+1,[](node A,node B){return A.b<B.b;});
    for(int i=n;i>=1;i--){
        for(int j=1;j<=n;j++)x[i]=a[i].a;
        sort(x+i,x+n+1);
        for(int j=1;j+i-1<=n;j++)
            s[i][j]=s[i][j-1]+x[i+j-1];
	} 
    double ans=inf;
    for(int cas=0;cas<=n;cas++){
		memset(f,0x7f,sizeof(f));	
		f[0][0]=0.0;
        for(int i=1;i<=n;i++)
            for(int j=0;j<=cas;j++){
				f[i][j]=min(f[i][j],f[i-1][j]+a[i].a/(cas+1));
				if(j&&a[i].b!=inf)f[i][j]=min(f[i][j],f[i-1][j-1]+a[i].b/j);	
			}
        for(int i=cas;i<=n;i++)
            ans=min(ans,f[i][cas]+s[i+1][k-i]/(cas+1));
        // cout<<ans<<"\n";
	}
    printf("%.15lf",(double)ans);
    return 0;
}