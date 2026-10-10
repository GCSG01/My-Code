#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
struct node{
	int c,l;
}tr[N<<2];
int n,m,fa[N];
int siz[N],rt[N],dis[N];
int ls[N],rs[N],sum[N];
void newnode(int now){
	siz[now]=1,rt[now]=now,sum[now]=tr[now].c;
}
int merge(int x,int y){
	if(!x||!y) return x+y;
	if(tr[x].c<tr[y].c)swap(x,y);
	rs[x]=merge(rs[x],y);
	if(dis[ls[x]]<dis[rs[x]])swap(ls[x],rs[x]);
	dis[x]=dis[rs[x]]+1;
	return x;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	int ans=0;
	for(int i=1,c,l;i<=n;i++){
		cin>>fa[i]>>c>>l,tr[i]={c,l},newnode(i);
		if(c<=m)ans=max(ans,l);
	}
	for(int i=n;i>1;i--){
		int x=fa[i],&now=rt[x];
		now=merge(rt[i],rt[x]);
		siz[x]+=siz[i],sum[x]+=sum[i];
		while(sum[x]>m)
			sum[x]-=tr[now].c,now=merge(ls[now],rs[now]),siz[x]--;
		ans=max(ans,tr[x].l*siz[x]);
	}
	cout<<ans;
}