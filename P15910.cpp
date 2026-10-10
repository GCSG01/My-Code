#include<bits/stdc++.h>
#define int __int128
using namespace std;
const int N=10,M=1.5e10,mod=1e10;
inline void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
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
};
matrix qpow(matrix A,int k){
    matrix ans(A.n,A.p);ans.init();
    for(;k;A=A*A,k>>=1)
        if(k&1)ans=ans*A;
    return ans;
}
int power(int x,int y,int p,int s=1){
    for(x%=p;y;x*=x,x%=p,y>>=1)
        if(y&1)s*=x,s%=p;
    return s;
}
int phi(int n){
    int ans=n;
    for(int i=2;i*i<=n;i++)
        if(n%i==0){
            ans=ans/i*(i-1);
            while(n%i==0)n/=i;
        }
    if(n>1)ans=ans/n*(n-1);
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    matrix f(2,mod),dp(2,mod);
    f[1][1]=1,f[1][2]=0,dp[1][1]=dp[1][2]=dp[2][1]=1;
    int m1=phi(M),m2=phi(m1),m3=phi(m2);
    int T;rd(T);
    while(T--){
        int n;rd(n);
        int l3=power(7,n%m3+(n>=m3?m3:0),m2);
        int l2=power(7,l3+m2,m1);
        int l1=power(7,l2+m1,M);
        printf("%010lld\n",(long long)((f*qpow(dp,l1-1))[1][1]));
    }
}