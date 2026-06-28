#include<bits/stdc++.h>
using namespace std;
const int N=30;
int a[N][N],b[N][N],c[N][N],d[N][N];
int n,m;
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1,x,y;i<=n;i++)
		cin>>x>>y,a[x][y]=a[y][x]=1;
	for(int i=1,x,y;i<=m;i++)
		cin>>x>>y,b[x][y]=b[y][x]=1;
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
			if(i!=j)
                for(int k=1;k<=9;k++)
                    if(k!=i&&k!=j)
                        if(a[i][j]&&b[i][k])
                            c[i][j]++,d[i][k]++;
	int cnt=0,p=0;
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
			if(c[i][j])
			{
				cnt++,p=i;
				break;
			}
	if(cnt==1)
        return cout<<p,0;
    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)
            if(c[i][j]&&c[j][i])return cout<<-1,0;
            else if(d[i][j]&&d[j][i])return cout<<-1,0;
    cout<<0;
	return 0;
}