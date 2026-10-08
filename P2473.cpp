#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=18,K=105;
int n,k,p[N],s[N];
double f[K][1<<N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>k>>n;
    for(int i=1,x;i<=n;i++){
        cin>>p[i];
        while(cin>>x&&x)
            s[i]|=(1<<(x-1));
    }
    for(int i=k;i>=1;i--)
        for(int j=0;j<(1<<n);j++){
            for(int l=1;l<=n;l++)
                if((j&s[l])==s[l])
                    f[i][j]+=max(f[i+1][j],f[i+1][j|(1<<(l-1))]+p[l]);
                else f[i][j]+=f[i+1][j];
            f[i][j]/=n;
        }
    printf("%.6lf",f[1][0]);
}