#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1<<23;
int a[N],mx1[N],mx2[N],n;
void upd(int &x,int &y,int v){
    if(v>x)y=x,x=v;
    else y=max(y,v);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],upd(mx1[a[i]],mx2[a[i]],i);
    for(int i=0;i<22;i++)
        for(int j=0;j<(1<<22);j++)
            if(!(j&(1<<i)))
                upd(mx1[j],mx2[j],mx1[j^(1<<i)]),
                upd(mx1[j],mx2[j],mx2[j^(1<<i)]);
    int ans=0;
    for(int i=1;i<=n-2;i++){
        int s=0,cnt=((1<<22)-1)^a[i];
        for(int j=22;j>=0;j--)
            if((cnt>>j)&1){
                s+=(1<<j);
                if(mx2[s]<=i)s-=(1<<j);
            }
        ans=max(ans,a[i]+s);
    }
    cout<<ans;
    return 0;
}