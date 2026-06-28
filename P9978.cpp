#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int s[N],t[N];
int a[N],b[N];
int v[N];
int n;
int main(){
    int k;
    cin>>n>>k;
    for(int i=1;i<=k;i++)cin>>a[i],s[a[i]]=i;
    for(int i=1;i<=k;i++)cin>>b[i],t[b[i]]=i;
    int ans=0,sum=0;
    for(int i=1;i<=n;i++)
        if(!s[i]&&!t[i])ans++;
    for(int i=1;i<=k;i++){
        int pos=s[b[i]];
        if(pos)v[(i+k-pos)%k]++;
    }
    for(int i=0;i<n;i++)
        sum=max(sum,v[i]);
    memset(v,0,sizeof v);
    for(int i=1;i*2<=k;i++)swap(b[i],b[k-i+1]);
    for(int i=1;i<=k;i++){
        int pos=s[b[i]];
        if(pos)v[(i+k-pos)%k]++;
    }
    for(int i=0;i<n;i++)
        sum=max(sum,v[i]);
    cout<<ans+sum;
    return 0;
}