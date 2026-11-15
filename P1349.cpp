#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=10;
int n,mod;
struct matrix{
    int n,p,a[N][N];
    matrix(int nn,int m):n(nn),p(m){memset(a,0,sizeof a);}
    void init(){
        for(int i=1;i<=n;i++)
            a[i][i]=1;
        return ;
    }
    int * operator[](int x){return a[x];}
    const int * operator[](int x)const{return a[x];}
    matrix operator*(const matrix &B)const{
        matrix res(n,p);
        for(int k=1;k<=n;k++)
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    (res[i][j]+=a[i][k]*B[k][j]%p)%=p;
        return res;
    }
    matrix operator+(const matrix &B)const{
        matrix res(n,p);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                res[i][j]=(a[i][j]+B[i][j])%p;
        return res;
    }
    void print(){
        for(int i=1;i<=n;i++,cout<<"\n")
            for(int j=1;j<=n;j++)
                cout<<a[i][j]<<" ";
        return ;
    }
};
matrix qpow(matrix A,int k){
    matrix ans(A.n,A.p);ans.init();
    for(;k;A=A*A,k>>=1)
        if(k&1)ans=ans*A;
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int p,q,f[3];
    cin>>p>>q>>f[1]>>f[2]>>n>>mod;
    matrix a(2,mod);
    a[1][1]=p,a[1][2]=q,a[2][1]=1;
    if(n==1)return cout<<f[1],0;
    if(n==2)return cout<<f[2],0;
    a=qpow(a,n-2);
    cout<<(f[2]*a[1][1]%mod+f[1]*a[1][2]%mod)%mod;
}