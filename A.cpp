#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,q,a[N];
struct node{
	int l,r,p;
};
vector<node>tmp;
set<int>pos[N];
int pre[N];
int mx[N<<2],tr[N<<2];
#define ls p<<1
#define rs p<<1|1
#define mid ((l+r)>>1)
inline int calc(int l,int r,int p,int v){
	if(l==r)return max(mx[p],v);
	if(mx[p]<=v)return (r-l+1)*v;
	if(mx[ls]<=v)return (mid-l+1)*v+calc(mid+1,r,rs,v);
	return tr[p]-tr[ls]+calc(l,mid,ls,v);
}
inline void push_up(int l,int r,int p){
	mx[p]=max(mx[ls],mx[rs]),tr[p]=tr[ls]+calc(mid+1,r,rs,mx[ls]);
}
void get(int l,int r,int p,int ql,int qr){
	if(l>qr||r<ql)return;
	if(ql<=l&&r<=qr)return tmp.push_back({l,r,p});
	get(l,mid,ls,ql,qr),get(mid+1,r,rs,ql,qr);
}
void update(int l,int r,int p,int x,int v){
	if(l==r)
		return mx[p]=tr[p]=v,void();
	if(x<=mid)update(l,mid,ls,x,v);
	if(x>mid)update(mid+1,r,rs,x,v);
	push_up(l,r,p);
}
inline void rd(int &x){
	char p=getchar();x=0;
	while(p<'0'||p>'9')p=getchar();
	while(p>='0'&&p<='9')x=x*10+p-'0',p=getchar();
}
inline void print(int x){
	if(x>9)print(x/10);
	putchar(x%10+'0');
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	rd(n),rd(q);
	for(int i=1;i<=n;i++){
		rd(a[i]);
		if(!pos[a[i]].empty())pre[i]=*prev(pos[a[i]].end());
		update(1,n,1,i,pre[i]),pos[a[i]].insert(i);
	}
	while(q--){
		int op,x,y;rd(op),rd(x),rd(y);
		if(op==1){
			tmp.clear(),get(1,n,1,x,y);
			int now=x-1,ans=y*(y+1)/2-x*(x-1)/2;
			for(auto [l,r,p]:tmp)
				ans-=calc(l,r,p,now),now=max(now,mx[p]);
			print(ans),puts("");
		}
		else{
			pos[a[x]].erase(x);
			auto it=pos[a[x]].upper_bound(x);
			if(it!=pos[a[x]].end()){
				if(it!=pos[a[x]].begin())pre[*it]=*prev(it);
				else pre[*it]=0;
				update(1,n,1,*it,pre[*it]);
			}
			a[x]=y;
			it=pos[y].upper_bound(x);
			if(it!=pos[y].end())
				pre[*it]=x,update(1,n,1,*it,pre[*it]);
			if(it!=pos[y].begin())pre[x]=*prev(it);
			else pre[x]=0;
			update(1,n,1,x,pre[x]),pos[y].insert(x);
		}
	}
}