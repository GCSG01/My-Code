#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=3e5+5;
int n,m,k;
int a[N];
vector<int>t[N];
struct node{
	int l,r,k;
}qu[N];
int Ans[N];
struct Node{
    int id,p;
}p[N],q1[N],q2[N];
int tr[N];
int lowbit(int x){return x&-x;}
void update(int x,int k){
	while(x<=m)
		tr[x]+=k,x+=lowbit(x);
}
int query(int x,int s=0){
	while(x)
        s+=tr[x],x-=lowbit(x);
	return s;
}
void add(int l,int r,int k){
	if(l<=r)return update(l,k),update(r+1,-k);
	update(l,k),update(m+1,-k),
    update(1,k),update(r+1,-k);
}
void solve(int l,int r,int ql,int qr){
	if(l==r){
		for(int i=ql;i<=qr;i++)
			Ans[p[i].id]=l;
		return;
	}
	int mid=l+r>>1;
	for(int i=l;i<=mid;i++)
		add(qu[i].l,qu[i].r,qu[i].k);
	int cnt1=0,cnt2=0;
	for(int i=ql;i<=qr;i++){
		__int128 sum=0;
		for(auto j:t[p[i].id])
			sum+=query(j);
		if(sum>=p[i].p)
            q1[++cnt1]=p[i];
		else q2[++cnt2]={p[i].id,p[i].p-(int)sum};
	}
	for(int i=l;i<=mid;i++)
		add(qu[i].l,qu[i].r,-qu[i].k);
	for(int i=1;i<=cnt1;i++)
		p[ql+i-1]=q1[i];
	for(int i=1;i<=cnt2;i++)
		p[ql+cnt1+i-1]=q2[i];
	solve(l,mid,ql,ql+cnt1-1);
	solve(mid+1,r,ql+cnt1,qr);
    return ;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		cin>>a[i],t[a[i]].push_back(i);
	for(int i=1;i<=n;i++)
		cin>>p[i].p,p[i].id=i;
	cin>>k;
	for(int i=1;i<=k;i++)
		cin>>qu[i].l>>qu[i].r>>qu[i].k;
	solve(1,k+1,1,n);
	for(int i=1;i<=n;i++)
		if(Ans[i]<=k)
			cout<<Ans[i]<<"\n";
		else cout<<"NIE"<<"\n";
	return 0;
}