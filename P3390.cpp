#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200+5;
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
matrix qpow(const matrix &A,int k){
	matrix ans(A.n,A.p);ans.init();
	matrix bas=A;
	for(;k;bas=bas*bas,k>>=1)
		if(k&1)ans=ans*bas;
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,k;cin>>n>>k;
	matrix a(n,1e9+7);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	a=qpow(a,k),a.print();
}