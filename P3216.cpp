#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
struct mat{
    int n,m,p,a[5][5];
    mat(int nn,int mm,int pp):n(nn),m(mm),p(pp){memset(a,0,sizeof a);}
    void init(){
        for(int i=1;i<=n;i++)
            a[i][i]=1;
        return ;
    }
    int * operator[](int x){return a[x];}
    const int * operator[](int x)const{return a[x];}
    mat operator*(const mat &B)const{
        mat res(min(n,B.n),min(m,B.m),p);
        for(int k=1;k<=n;k++)
            for(int i=1;i<=B.m;i++)
                for(int j=1;j<=m;j++)
                    (res[i][j]+=a[i][k]*B[k][j]%p)%=p;
        return res;
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
int n,p;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>p;
    mat a(1,3,p),b(3,3,p);
	a[2][1]=a[3][1]=1;
	b[1][2]=b[2][2]=b[2][3]=b[3][3]=1;
	for(int k=10;;k*=10){
		b[1][1]=k%p;
		if(n<k){
			a=qpow(b,n-k/10+1)*a;
			break;
		}
		a=qpow(b,k-k/10)*a;
	}
	cout<<a[1][1];
    return 0;
}