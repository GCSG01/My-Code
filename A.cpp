#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int a[N];
signed main() {
    ios::sync_with_stdio(0);cin.tie(0);
    int c,t;cin>>c>>t;
    while (t--){
        int n,k;cin>>n>>k;
		for(int i=1;i<=n;i++)cin>>a[i];
        int s=0;
		for(int i=1;i<=n;i++)s|=a[i];
        int mx=0,id=0;
		for(int i=1;i<=n;i++){
            int sum=a[i]+k;
            for(int j=1;j<n;j++){
                if(j==i)continue;
                sum|=a[j];
            }
            if(sum>mx)
                mx=sum,id=i;
        }
        cout<<mx<<"\n";
        for(int i=1;i<=n;i++){
			if(i==id)cout<<k;
			else cout<<0;
			cout<<" ";
        }
		cout<<"\n";
    }
    return 0;
}