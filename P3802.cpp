#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5,mod=1e9+7;
int a[8],n=7;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int k=0;
    for(int i=1;i<=n;i++)cin>>a[i],k+=a[i];
    double ans=1*2*3*4*5*6*7;
    for(int i=1;i<n;i++)ans=ans*a[i]/(k-i+1);
    printf("%.3f",ans*a[7]);
}