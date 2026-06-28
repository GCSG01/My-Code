#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e3+5,p=1e9+7;
int a[N][N];
int n;
int power(int a,int b){
    int s=1;
    while(b){
        if(b&1)s=s*a,s%=p;
        a=a*a,a%=p,b>>=1;
    }
    return s;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>a[i][j];
    for(int i=1;i<=n;i++)
        a[i][n+i]=1;
    for(int i=1;i<=n;i++){
        int pos=i;
        for(int j=i+1;j<=n;j++)
            if(a[j][i]>a[pos][i])pos=j;
        if(pos!=i)swap(a[i],a[pos]);
        if(!a[i][i])return cout<<"No Solution",0;
        int inv=power(a[i][i],p-2);
        for(int k=1;k<=n;k++)
            if(k!=i){
                int cnt=a[k][i]*inv%p;
                for(int j=i;j<=n*2;j++)
                    a[k][j]+=p-a[i][j]*cnt%p,a[k][j]%=p;
            }
        for(int j=1;j<=n*2;j++)a[i][j]=a[i][j]*inv%p;
    }
    for(int i=1;i<=n;i++,cout<<"\n")
        for(int j=1;j<=n;j++)
            cout<<a[i][j+n]<<" ";
    return 0;
}