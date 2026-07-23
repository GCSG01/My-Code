#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
using namespace std;
const int N=5e3;
const double eps=1e-19;
int a[N][N];
pair<int,int>e[N*N];
int tot,n;
int check(int px,int py){
	int sum=0;
	for(int i=1;i<=n;i++)
		if(a[px][py]){
            if(a[py][i]==1&&a[i][px]==1)sum++;
        }
		else if(a[px][i]==1&&a[i][py]==1)sum++;
	swap(a[px][py],a[py][px]);
	for(int i=1;i<=n;i++)
		if(a[px][py]){
            if(a[py][i]==1&&a[i][px]==1)sum--;
        }
		else if(a[px][i]==1&&a[i][py]==1)sum--;
	swap(a[px][py],a[py][px]);
	return sum;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>a[i][j];
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            if(a[i][j]==2)e[++tot]={i,j},a[i][j]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<i;j++)
            if(a[i][j]==2)a[i][j]=0;
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            for(int k=j+1;k<=n;k++)
                if(a[i][j]==1&&a[j][k]==1&&a[k][i]==1)ans++;
                else if(a[i][j]==0&&a[j][k]==0&&a[k][i]==0)ans++;
    double temp=5000,delta=0.9998;
    while(temp>eps){
        int x=rand()%tot+1;
        int px=e[x].fi,py=e[x].se;
        swap(a[px][py],a[py][px]);
        int cnt=check(px,py);
        if(cnt>0||exp(cnt/temp)>(double)rand()/(double)RAND_MAX)
            ans+=cnt;
        else swap(a[px][py],a[py][px]);
        temp*=delta;
    }
    cout<<ans<<"\n";
    for(int i=1;i<=n;i++,cout<<"\n")
        for(int j=1;j<=n;j++)
            cout<<a[i][j]<<" ";
    return 0;
}