#include<bits/stdc++.h>
#define ll unsigned long long
using namespace std;
const int N=2.5e6+10;
const ll mod=1e9+7;
int n,m,a[N],q[N];
ll f[N];
ll s1[N],s2[N],mn1[N],mn2[N];
int t1,t2;
inline void push_back(ll x){
    s2[++t2]=x;
    mn2[t2]=min(mn2[t2-1],x);
}
inline void build(int o){
    static ll w[N];
    int i,cnt=t1+t2,m=(cnt>>1)+o;
    for(i=1;i<=t1;i++)
        w[t1-i]=s1[i];
    for(i=1;i<=t2;i++)
        w[t1+i-1]=s2[i];
    t1=t2=0;
    mn1[0]=mn2[0]=~0ull;
    for(i=m-1;i>=0;i--)
        s1[++t1]=w[i],mn1[t1]=min(mn1[t1-1],s1[t1]);
    for(i=m;i<cnt;i++)
        s2[++t2]=w[i],mn2[t2]=min(mn2[t2-1],s2[t2]);
    return ;
}
inline void pop_front(){
    if(!t1)build(1);
    t1--;
}
inline void pop_back(){ 
    if(!t2)build(0);
    t2--;
}
int solve(int n,int m,int a[]){
    for(int i=n;i>=1;i--)
        a[i]=a[i-1];
    a[0]=t1=t2=0;
    mn1[0]=mn2[0]=~0ull;
    ll ans=0;
    int l=1,r=0;
    for(int i=1;i<=n;i++){
        while(l<=r&&a[q[r]]<=a[i]){
            r--;
            if(l<=r)pop_back();
        }
        while(l<=r&&q[l]<i-m){
            l++;
            if(l<=r)pop_front();
        }
        if(l<=r)
            push_back(f[q[r]]+a[i]);
        q[++r]=i,f[i]=min({mn1[t1],mn2[t2],f[max(i-m,0)]+a[q[l]]});
        ans=(ans*23ull+f[i])%mod;
    }
    return ans;
}
#ifndef ONLINE_JUDGE
int main(){
    int n,k;cin>>n>>k;
    for(int i=0;i<n;i++)
        cin>>a[i];
    cout<<solve(n,k,a);
}
#endif