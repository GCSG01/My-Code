#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n;
int a[N],l[N],r[N];
int ans[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],a[i+n]=a[i];
    l[1]=0;
    for(int i=2;i<=n+n;i++){
        int x=i-1;
        while(x&&a[x]>=a[i])x=l[x];
        l[i]=x;
    }
    r[n+n]=n+n+1;
    for(int i=n+n-1;i>=1;i--){
        int x=i+1;
        while(x<=n+n&&a[x]>a[i])x=r[x];
        r[i]=x;
    }
    int mn=1,sum=0;
    for(int i=1;i<=n;i++){
        sum+=a[i];
        if(a[mn]>a[i])mn=i;
    }
    // cout<<mn<<" ";
    // return 0;
    for(int i=mn+1;i<=mn+n;i++){
        if(a[i]==a[mn])continue;
        int c=r[i]-l[i]-1,k=a[i]-max(a[l[i]],a[r[i]]);
        // cout<<c+1<<" "<<k<<"\n";
        ans[1]+=k,ans[c+1]-=k;
    }
    for(int i=1;i<=n;i++)ans[i]+=ans[i-1];
    for(int i=1;i<=n;i++)ans[i]+=ans[i-1];
    for(int i=1;i<=n;i++)cout<<sum-ans[i]<<"\n";
    return 0;
}