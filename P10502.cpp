#include<bits/stdc++.h>
using namespace std;
const int N=35;
struct mat{
    int n,p,a[N][N];
    mat(int nn,int m):n(nn),p(m){memset(a,0,sizeof a);}
    void init(){
        for(int i=1;i<=n;i++)
            a[i][i]=1;
        return ;
    }
    int * operator[](int x){return a[x];}
    const int * operator[](int x)const{return a[x];}
    mat operator*(const mat &B)const{
        mat res(n,p);
        for(int k=1;k<=n;k++)
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    (res[i][j]+=a[i][k]*B[k][j]%p)%=p;
        return res;
    }
    mat operator+(const mat &B)const{
        mat res(n,p);
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
mat qpow(mat A,int k){
    mat ans=A;k--;
    while(k){
        if(k&1)ans=ans*A;
        A=A*A,k>>=1;
    }
    return ans;
}
int n,m,k;
mat a(0,0);
mat get(int k){
    if(k==1)return a;
    mat b=get(k/2);
    b=b+qpow(a,k/2)*b;
    if(k%2)b=b+qpow(a,k);
    return b;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>k>>m;
    a.n=n,a.p=m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>a[i][j];
    get(k).print();
    return 0;
}