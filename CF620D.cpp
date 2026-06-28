#include<bits/stdc++.h>
using namespace std;
const int N=2e3+5;
int n,m,sa,sb;
int a[N],b[N];
int aa[N*N],bb[N*N];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],sa+=a[i];
    cin>>m;
    for(int i=1;i<=m;i++)cin>>b[i],sb+=b[i];
    int ans=abs(sa-sb);
    sort(a+1,a+n+1);
    sort(b+1,b+m+1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            ans=min(ans,abs(sa-sb+b[j]*2-a[i]*2));
    int ta=0,tb=0;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            aa[++ta]=a[i]+a[j];
    for(int i=1;i<=m;i++)
        for(int j=i+1;j<=m;j++)
            bb[++tb]=b[i]+b[j];
    sort(aa+1,aa+ta+1);
    sort(bb+1,bb+tb+1);
    for(int i=1;i<=ta;i++){
        int sum=0;
        int l=0,r=tb+1;
        while(l<r){
            int mid=(l+r)>>1;
            if(bb[mid]>=aa[i])r=mid;
            else l=mid+1;
        }
        ans=max(ans,sa-sb+bb[r]-aa[i]);
    }
    return 0;
}