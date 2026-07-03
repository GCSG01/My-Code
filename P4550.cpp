#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5;
double g[N],f[N];
int n;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=n-1;i>=0;i--)
        f[i]=f[i+1]+n*1.000/(n-i),
        g[i]=f[i+1]+g[i+1]+(f[i]+1)*i*1.000/(n-i)+1;
    printf("%.2f",g[0]);
    return 0;
}