#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
struct node{
	int a,b,c,ans,sum;
}a[N],b[N];
int n,m,len;
int ans[N];
int tree[N];
inline int lowbit(int x){return x&-x;}
void update(int x,int k){
	while(x<=m)tree[x]+=k,x+=lowbit(x);
	return ;
}
int get(int x,int s=0){
	while(x)s+=tree[x],x-=lowbit(x);
	return s;
}
bool cmp(node a,node b){
    return a.a!=b.a?a.a<b.a:(a.b!=b.b?a.b<b.b:a.c<b.c);
}
bool cmp2(node a,node b){
    return a.b!=b.b?a.b<b.b:a.c<b.c;
}
void cdq(int l,int r){
	if(l>=r)return;
	int mid=(l+r)>>1;
	cdq(l,mid),cdq(mid+1,r);
	sort(a+l,a+mid+1,cmp2);
	sort(a+mid+1,a+r+1,cmp2);
	int i,j;
	for(i=mid+1,j=l;i<=r;i++){
		while(j<=mid&&a[j].b<=a[i].b)
			update(a[j].c,a[j].sum),j++;
		a[i].ans+=get(a[i].c);
	}
	for(i=l;i<j;i++)
		update(a[i].c,-a[i].sum);
	return ;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>b[i].a>>b[i].b>>b[i].c;
	sort(b+1,b+1+n,cmp);
	int tot=1;
	for(int i=2;i<=n;i++)
		if(b[i].a!=b[i-1].a||b[i].b!=b[i-1].b||b[i].c!=b[i-1].c)
			a[++len]=(node){b[i-1].a,b[i-1].b,b[i-1].c,0,tot},tot=1;
		else tot++;
	a[++len]=(node){b[n].a,b[n].b,b[n].c,0,tot};
	cdq(1,len);
	for(int i=1;i<=len;i++)
		ans[a[i].ans+a[i].sum-1]+=a[i].sum;
	for(int i=0;i<n;i++)
		cout<<ans[i]<<"\n";
	return 0;
}