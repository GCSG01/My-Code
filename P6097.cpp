#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=(1<<21)+5,mod=1e9+9;
int n;
int a[21][N],b[21][N],s[21][N];
void XOR(int *a,int flag){
    for(int i=1;i<n;i<<=1)
        for(int j=0;j<n;j+=(i<<1))
            for(int k=0;k<i;k++)
                (a[j+k+i]+=a[j+k]*flag+mod)%=mod;
    return ;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int lim;
    cin>>lim,n=1<<lim;
    for(int i=0;i<n;i++)cin>>a[__builtin_popcount(i)][i];
    for(int i=0;i<n;i++)cin>>b[__builtin_popcount(i)][i];
    for(int i=0;i<=lim;i++)
        XOR(a[i],1),XOR(b[i],1);
    for(int i=0;i<=lim;i++)
        for(int j=0;j<=i;j++)
            for(int k=0;k<n;k++)
                (s[i][k]+=a[j][k]*b[i-j][k]%mod)%=mod;
    for(int i=0;i<=lim;i++)
        XOR(s[i],-1);
    for(int i=0;i<n;i++)
        cout<<s[__builtin_popcount(i)][i]<<" ";
    return 0;
}