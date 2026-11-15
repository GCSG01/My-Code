#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e7+5;
int n,A,B,C;
int a[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>A>>B>>C>>a[1];
    for(int i=2;i<=n;i++)a[i]=(a[i-1]*A+B)%100000001;
    for(int i=1;i<=n;i++)a[i]=a[i]%C+1;
    double ans=0;
    for(int i=1;i<n;i++)
        ans+=1.0/max(a[i],a[i+1]);
    ans+=1.0/max(a[1],a[n]);
    printf("%.3lf",ans);
}