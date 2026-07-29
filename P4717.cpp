#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1.5e7+5,mod=998244353;
int n,m;
int a[N],b[N],A[N],B[N];
int qpow(int x,int y){
    int s=1;
    while(y){
        if(y&1)s=s*x%mod;
        x=x*x%mod,y>>=1;
    }
    return s;
}
void OR(int *a,int x=1){
    for(int k=1;k*2<=n;k*=2)
        for(int i=0;i<n;i+=k*2)
            for(int j=0;j<k;j++)
                (a[i+j+k]+=a[i+j]*x%mod)%=mod;
}
void AND(int *a,int x=1){
    for(int k=1;k*2<=n;k*=2)
        for(int i=0;i<n;i+=k*2)
            for(int j=0;j<k;j++)
                (a[i+j]+=a[i+j+k]*x)%=mod;
}
void XOR(int *a,int x=1){
    for(int k=1;k*2<=n;k*=2)
        for(int i=0;i<n;i+=k*2)
            for(int j=0;j<k;j++){
                (a[i+j]+=a[i+j+k])%=mod;
                a[i+j+k]=(a[i+j]-a[i+j+k]-a[i+j+k]+mod+mod)%mod;
                a[i+j]*=x,a[i+j+k]*=x;
                a[i+j]%=mod,a[i+j+k]%=mod;
            }
}
signed main() {
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>m,n=1<<m;
    for(int i=0;i<n;i++)cin>>A[i];
    for(int i=0;i<n;i++)cin>>B[i];

    for(int i=0;i<n;i++)a[i]=A[i],b[i]=B[i];
    OR(a),OR(b);
    for(int i=0;i<n;i++)(a[i]*=b[i])%=mod;
    OR(a,mod-1);
    for(int i=0;i<n;i++)cout<<a[i]<<" ";
    cout<<"\n";

    for(int i=0;i<n;i++)a[i]=A[i],b[i]=B[i];
    AND(a),AND(b);
    for(int i=0;i<n;i++)(a[i]*=b[i])%=mod;
    AND(a,mod-1);
    for(int i=0;i<n;i++)cout<<a[i]<<" ";
    cout<<"\n";

    for(int i=0;i<n;i++)a[i]=A[i],b[i]=B[i];
    XOR(a),XOR(b);
    for(int i=0;i<n;i++)(a[i]*=b[i])%=mod;
    XOR(a,qpow(2,mod-2));
    for(int i=0;i<n;i++)cout<<a[i]<<" ";
    cout<<"\n";
}