#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[35];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        int ans=0,flag=0;
        if(a[n])flag=1;
        for(int i=1;i<n;i++){
            if(a[i])flag=1;
            if(a[i]<2*a[i+1]){
                ans=flag=-1;break;
            } 
            ans=max(ans,a[i]-2*a[i+1]);
        }
        cout<<max(ans,flag)<<"\n";
    }
}