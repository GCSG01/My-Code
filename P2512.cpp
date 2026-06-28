#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+5;
int a[N],x[N];
int sum,n;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],sum+=a[i];
    sum/=n;
    for(int i=1;i<=n;i++)
        x[i]=x[i-1]-a[i]+sum;
    sort(x+1,x+n+1);
    int cnt=0;
    if(n%2)cnt=x[n/2+1];
    else cnt=x[n/2]+x[n/2+1],cnt/=2;
    int ans=0;
    for(int i=1;i<=n;i++)
        ans+=abs(x[i]-cnt);
    cout<<ans;
    return 0;
}