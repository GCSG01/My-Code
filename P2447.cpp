#include<bits/stdc++.h>
using namespace std;
const int N=2e3+5;
bitset<N>a[N];
int n,m;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        char x;
        for(int j=1;j<=n;j++)
            cin>>x,a[i][j]=x-'0';
        cin>>x,a[i][n+1]=x-'0';
    }
	int now,ans=0;
	for(int i=1;i<=n;i++){
		now=i;
		while(now<=m&&!a[now][i])now++;
		if(now==m+1)
            return cout<<"Cannot Determine",0;
		ans=max(ans,now);
		if(now!=i)swap(a[now],a[i]);
		for(int j=1;j<=m;j++)
			if(j!=i&&a[j][i])
                a[j]^=a[i];
	}
	cout<<ans;
	for(int i=1;i<=n;i++)
        cout<<(a[i][n+1]?"\n?y7M#":"\nEarth");
}