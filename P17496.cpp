#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
vector<int>a,f;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);	
	cin>>n;
    for(int i=1;i<=n*2;i*=2)
        for(int j=i;j<=n*2;j*=3)
            if(j!=1)a.push_back(j);
	sort(a.begin(),a.end());
	for(int i:a)
        if(i%3==0)f.push_back(i/3);
        else f.push_back(i/2);
    int ans=0;
    while(n>1){
        int l=lower_bound(a.begin(),a.end(),n)-a.begin(),r=lower_bound(a.begin(),a.end(),n*2)-a.begin()-1;
        int mx=0;
        for(int i=l;i<=r;i++)
            mx=max(mx,f[i]);
        n=mx,ans++;
    }
    cout<<ans;
}