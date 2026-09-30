#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
struct node{
	int a,b,c,ans,sum;
}a[N],b[N];
int n,m,K,Ans[N],tr[N];
inline int lowbit(int x){return x&-x;}
inline void add(int x,int k){
	while(x<=K)tr[x]+=k,x+=lowbit(x);
}
inline int query(int x,int s=0){
	while(x)s+=tr[x],x-=lowbit(x);
	return s;
}
bool cmp(node a,node b){
    return a.b!=b.b?a.b<b.b:a.c<b.c;
}
void cdq(int l,int r){
	if(l>=r)return ;
	int mid=(l+r)>>1;
	cdq(l,mid),cdq(mid+1,r);
	sort(a+l,a+mid+1,cmp);
	sort(a+mid+1,a+r+1,cmp);
	int j=l;
	for(int i=mid+1;i<=r;i++){
		while(j<=mid&&a[j].b<=a[i].b)
			add(a[j].c,a[j].sum),j++;
		a[i].ans+=query(a[i].c);
	}
	while(j>l)j--,add(a[j].c,-a[j].sum);
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>m>>K;
	for(int i=1;i<=m;i++)cin>>b[i].a>>b[i].b>>b[i].c;
	sort(b+1,b+m+1,[](node A,node B){
		return A.a!=B.a?A.a<B.a:(A.b!=B.b?A.b<B.b:A.c<B.c);
	});
	int cnt=1;n=0;
	for(int i=2;i<=m;i++){
		if(b[i].a!=b[i-1].a||b[i].b!=b[i-1].b||b[i].c!=b[i-1].c)
			a[++n]=b[i-1],a[n].sum=cnt,cnt=1;
		else cnt++;
	}
	a[++n]=b[m],a[n].sum=cnt;
	cdq(1,n);
	for(int i=1;i<=n;i++)
		Ans[a[i].ans+a[i].sum-1]+=a[i].sum;
	for(int i=0;i<m;i++)
		cout<<Ans[i]<<"\n";
}