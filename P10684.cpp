#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+5,inf=1e18;
int n,q,a[3][N];
int s[N],tot[2],c[N];
int tr[N*4],tag[N*4];
#define ls p<<1
#define rs p<<1|1
#define mid ((l+r)>>1)
inline void upd(int p,int k){
	tr[p]+=k,tag[p]+=k;
}
void push_down(int p){
	upd(ls,tag[p]),upd(rs,tag[p]),tag[p]=0;
}
void build(int l,int r,int p){
	if(l==r)
		return tr[p]=c[l]*2-l-l*(l+1)/2-(tot[0]-l)*(tot[0]-l+1)/2,void();
	build(l,mid,ls),build(mid+1,r,rs),tr[p]=min(tr[ls],tr[rs]);
}
void upd(int l,int r,int p,int ql,int qr,int k){
	if(ql<=l&&r<=qr)
		return upd(p,k);
	push_down(p);
	if(ql<=mid)upd(l,mid,ls,ql,qr,k);
	if(qr>mid)upd(mid+1,r,rs,ql,qr,k);
	tr[p]=min(tr[ls],tr[rs]);
}
int query(int l,int r,int p,int ql,int qr){
	if(ql<=l&&r<=qr)return tr[p];
	push_down(p);
	int res=inf;
	if(ql<=mid)res=min(res,query(l,mid,ls,ql,qr));
	if(qr>mid)res=min(res,query(mid+1,r,rs,ql,qr));
	return res;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>q;
	for(int i=1;i<=2;i++)
		for(int j=1;j<=n;j++){
			char c;cin>>c,a[i][j]=(c=='C'),tot[a[i][j]]++;
		}
	int sum=0,cnt=0;
	for(int i=1;i<=n;i++){
		if(!a[1][i])sum+=i;
		if(!a[2][i])sum+=i,cnt++;
	}
	for(int i=1;i<=n;i++)
		s[i]=(!a[1][i])+(!a[2][i])+s[i-1];
	for(int i=1,w;i<=n;i++){
		if(s[i]<=i)continue;
		c[0]+=s[i]-i,c[1]+=-1-s[i]+i;
		c[s[i]-i+1]+=1;
	}
	for(int i=1;i<=tot[0];i++)c[i]+=c[i-1];
	for(int i=1;i<=tot[0];i++)c[i]+=c[i-1];
	int l=0,r=tot[0]/2,ql=max(0ll,tot[0]-n);
	build(l,r,1);
	cout<<query(l,r,1,ql,cnt)+sum+cnt<<"\n";
	for(int i=1;i<=n;i++)s[i]-=i;
	while(q--){
		int op,x,y,d;cin>>op>>x>>y;
		if(op==1){
			if(a[x][y]==a[x][y+1])d=0;
			else if(a[x][y]==0)d=-1;
			else d=1;
			if(d==1){
				if(s[y]>=0)
					upd(l,r,1,0,s[y],2);
				s[y]++,sum--;
			}
			if(d==-1){
				s[y]--,sum++;
				if(s[y]>=0)
					upd(l,r,1,0,s[y],-2);
			}
			swap(a[x][y],a[x][y+1]);
			cout<<query(l,r,1,ql,cnt)+sum+cnt<<"\n";
		}
		else{
			cnt-=!a[2][y],swap(a[1][y],a[2][y]),cnt+=!a[2][y];
			cout<<query(l,r,1,ql,cnt)+sum+cnt<<"\n";
		}
	}
}