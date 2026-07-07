#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,k;
int e[N],f[N],s[N];
int v[N];
int q[N],l,r=1;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>e[i],s[i]=s[i-1]+e[i];
    for(int i=1;i<=n;i++){
        v[i]=f[i-1]-s[i];
        while(l<=r&&v[q[r]]<v[i])r--;
        q[++r]=i;
        while(l<=r&&q[l]<i-k)l++;
        f[i]=v[q[l]]+s[i];
    }
    cout<<f[n];
    return 0;
}