#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,m,ans;
int a[N],b[N];
int x[N],y[N],xx[N],yy[N];
inline int get(int x,int y){
    return (x-1)*m+y;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[get(i,j)],x[i]+=a[get(i,j)],y[j]+=a[get(i,j)];
	int sum=0;
	for(int i=1;i<=n;i++)xx[i]=x[i];
	for(int i=1;i<=m;i++)yy[i]=y[i];
	sort(xx+1,xx+n+1,[](int A,int B){
        return A>B;
    });
	sort(yy+1,yy+m+1,[](int A,int B){
        return A>B;
    });

	for(int i=1;i<=4;i++)sum+=xx[i];
	ans=sum,sum=0;
	for(int i=1;i<=4;i++)sum+=yy[i];
	ans=max(ans,sum),sum=0;

	for(int i=1;i<=n;i++){
		int mx1=0,mx2=0,mx3=0;
		for(int j=1;j<=m;j++){
			int cnt=y[j]-a[get(i,j)];
			if(cnt>=mx1)
                mx3=mx2,mx2=mx1,mx1=cnt;
            else if(cnt>=mx2)
                mx3=mx2,mx2=cnt;
            else if(cnt>=mx3)
                mx3=cnt;
		}
		ans=max(ans,mx1+mx2+mx3+x[i]);
	}
	for(int i=1;i<=m;i++){
		int mx1=0,mx2=0,mx3=0;
		for(int j=1;j<=n;j++){
			int cnt=x[j]-a[get(j,i)];
			if(cnt>=mx1)
                mx3=mx2,mx2=mx1,mx1=cnt;
            else if(cnt>=mx2)
                mx3=mx2,mx2=cnt;
            else if(cnt>=mx3)
                mx3=cnt;
		}
		ans=max(ans,mx1+mx2+mx3+y[i]);
	}

	if(n>m){
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				b[get(j,i)]=a[get(i,j)];
		swap(n,m);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				a[i-get(i,j)]=b[get(i,j)];
	}

    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++){
            int mx1=0,mx2=0;
            for(int k=1;k<=m;k++){
                int cnt=y[k]-a[get(i,k)]-a[get(j,k)];
				if(cnt>=mx1)
                    mx2=mx1,mx1=cnt;
                else if(cnt>=mx2)
                    mx2=cnt;
			}
			ans=max(ans,mx1+mx2+x[i]+x[j]);
		}
	cout<<ans;	
	return 0;
}