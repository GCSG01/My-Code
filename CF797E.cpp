#include<bits/stdc++.h>
// #define int long long
using namespace std;
const int N=1e5+5,K=405;
int n,q;
int a[N];
int f[N][K];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=n;i>=1;i--)
		for(int j=1;j<=K-2;j++)
			if(i+a[i]+j>n)f[i][j]=1;
			else f[i][j]=f[i+a[i]+j][j]+1;
    cin>>q;
    while(q--){
        int p,k;cin>>p>>k;
        if(k<=K-5)cout<<f[p][k]<<"\n";
        else{
            int ans=0;
            while(p<=n)
                p+=a[p]+k,ans++;
            cout<<ans<<"\n";
        }
    }
    return 0;
}
/*
lalalalall
sLMxf
GCSG01
*/