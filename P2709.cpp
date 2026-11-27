#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,m,k,bk,a[N];
int pos[N];
array<int,3>e[N];
int Ans[N],ans;
int t[N];
void update(int x,int k){
	x=a[x],ans-=t[x]*t[x];
	t[x]+=k,ans+=t[x]*t[x];
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m>>k,bk=sqrt(n);
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)pos[i]=i/bk;
	for(int i=1;i<=m;i++)
		cin>>e[i][0]>>e[i][1],e[i][2]=i;
	sort(e+1,e+m+1,[](auto A,auto B){
		if(pos[A[0]]==pos[B[0]])
			return (pos[A[0]]&1?A[1]>B[1]:A[1]<B[1]);
		return A[0]<B[0];
	});
	int l=1,r=0;
	for(int i=1;i<=m;i++){
		int ql=e[i][0],qr=e[i][1];
		while(r<qr)update(++r,1);
		while(r>qr)update(r--,-1);
		while(l>ql)update(--l,1);
		while(l<ql)update(l++,-1);
		Ans[e[i][2]]=ans;
	}
	for(int i=1;i<=m;i++)
		cout<<Ans[i]<<"\n";
}