#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=605;
int n,p,a[N][N];
int gauss(){
    int ans=1;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++){
            while(a[i][i]){
                int d=a[j][i]/a[i][i];
                for(int k=i;k<=n;k++)
                    a[j][k]=(a[j][k]-d*a[i][k]%p+p)%p;
                swap(a[i],a[j]),ans=-ans;
            }
            swap(a[i],a[j]),ans=-ans;
        }
    for(int i=1;i<=n;i++)
        (ans*=a[i][i])%=p;
    return (ans+p)%p;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>p;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>a[i][j];
    cout<<gauss();
}