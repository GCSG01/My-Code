#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int a[N];
int s[N];
int f[N];
int g[N];
int n,c;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>c;
    for(int i=1;i<=n;i++)cin>>a[i];
    int ans=0;
    for(int i=1;i<=n;i++){
        f[a[i]]=min(f[a[i]],s[a[i]]-s[c]);
        s[a[i]]++;
        ans=max(ans,s[a[i]]-s[c]-f[a[i]]);
    }
    cout<<ans+s[c];
    return 0;
}