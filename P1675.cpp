#include <bits/stdc++.h>
using namespace std;
const int N=1e4+5;
mt19937 rnd(time(0));
int k,n;
struct node{
	int id,w;
	bool operator<(const node &B)const{
		return w>B.w;
	}
}cs[N],a[N],b[N],c[N];
int sa,sb;
void init(){
	for(int i=1;i<=2*k;i++)
		swap(cs[i],cs[rnd()%(k<<1)+1]);
	sa=sb=0;
	for(int i=1;i<=k;i++)
		sa+=cs[i].w,a[i]=cs[i];
	for(int i=1;i<=k;i++)
		sb+=cs[i+k].w,b[i]=cs[i+k];
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>k,n=3*k;
	for(int i=1;i<=n;i++)
		cin>>cs[i].w,cs[i].id=i;
	sort(cs+1,cs+n+1);
	for(int i=1;i<=k;i++)c[i]=cs[i+(k<<1)];
	init();
	int cnt=0;
	while(sa<=500*k||sb<=500*k){
		int i=rnd()%k+1,j=rnd()%k+1;
		int suma=sa+b[j].w-a[i].w;
		int sumb=sb+a[i].w-b[j].w;
		if(min(suma,sumb)>min(sa,sb))
			swap(a[i],b[j]),sa=suma,sb=sumb;
		if(++cnt%3000==0)init();
	}
	for(int i=1;i<=k;i++)cout<<a[i].id<<"\n";
	for(int i=1;i<=k;i++)cout<<b[i].id<<"\n";
	for(int i=1;i<=k;i++)cout<<c[i].id<<"\n";
}