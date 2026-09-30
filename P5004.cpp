#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int mod=1e9+7,N=2e7+5,M=20;
int f[N];
struct mat{
    int a[M][M];
    int *operator[](int x){return a[x];}
    const int *operator[](int x)const{return a[x];}
};
mat operator*(mat A,mat B){
    mat C={};
    for(int i=1;i<=16;i++)
        for(int k=1;k<=16;k++)
            for(int j=1;j<=16;j++)
                C[i][j]=(C[i][j]+A[i][k]*B[k][j]%mod)%mod;
    return C;
}
mat qpow(mat x,int y){
    mat s=x;y--;
    while(y){
        if(y&1)s=s*x;
        x=x*x,y>>=1;
    }
    return s;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n,m,ans=0;cin>>n>>m,m++;
    mat a={};
    a[1][1]=a[1][m]=1;
    for(int i=2;i<=m;i++)
        a[i][i-1]=1;
    cout<<qpow(a,n+m-1)[1][1];
}