#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int n;
int a[N];
int st[N],top;
int l1[N],r1[N];
int rt[N],b[N];
void ins(int x){
    bool vis=1;
	while(top&&a[st[top]]<a[x])top--,vis=0;
	if(top)r1[st[top]]=x;
	if(!vis)l1[x]=st[top+1];
	st[++top]=x;
}
struct node{
    int ls,rs,v;
}tr[N<<4];
int tot=0;
#define ls(p) tr[(p)].ls
#define rs(p) tr[(p)].rs
#define mid ((l+r)>>1)
void build(int l,int r,int p){
	if(l==r)return;
	ls(p)=++tot,rs(p)=++tot;
	build(l,mid,ls(p)),build(mid+1,r,rs(p));
}
void insert(int x,int l,int r,int p1,int p2){
	tr[p2]=tr[p1];
	if(l==r)
		return tr[p2].v++,void();
	if(x<=mid)
        ls(p2)=++tot,insert(x,l,mid,ls(p1),ls(p2));
	else rs(p2)=++tot,insert(x,mid+1,r,rs(p1),rs(p2));
	tr[p2].v=tr[ls(p2)].v+tr[rs(p2)].v;
}
int query(int l,int r,int s,int t,int p1,int p2){
	if(s>t)return 0;
	if(s<=l&&r<=t)
		return tr[p2].v-tr[p1].v;
	int sum=0;
	if(s<=mid)sum+=query(l,mid,s,t,ls(p1),ls(p2));
	if(mid+1<=t)sum+=query(mid+1,r,s,t,rs(p1),rs(p2));
	return sum;
}
int ans,len;
bool flag;
void solve(int l,int r,int m){
	if(l>=r)return;
	if(m-l<r-m)
		for(int i=l;i<m;i++){
			int w=upper_bound(b+1,b+len+1,b[a[m]]/b[a[i]])-b-1;
			ans+=query(1,len,1,w,rt[m],rt[r]);
		}
	else
        for(int i=m+1;i<=r;i++){
			int w=upper_bound(b+1,b+len+1,b[a[m]]/b[a[i]])-b-1;
			ans+=query(1,len,1,w,rt[l-1],rt[m-1]);
		}
	ans+=flag*query(1,len,1,1,rt[l-1],rt[r]),ans-=flag&(a[m]==1);
	solve(l,m-1,l1[m]),solve(m+1,r,r1[m]);
}
signed main(){
    ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i],b[i]=a[i];
		if(a[i]==1)ans++,flag=1;
	}
	sort(b+1,b+n+1);
	len=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(b+1,b+len+1,a[i])-b;
	for(int i=1;i<=n;i++)ins(i);
	rt[0]=1,build(1,n,1);
	for(int i=1;i<=n;i++)
		rt[i]=++tot,insert(a[i],1,len,rt[i-1],rt[i]);
	solve(1,n,st[1]);
	cout<<ans;
	return 0;
}