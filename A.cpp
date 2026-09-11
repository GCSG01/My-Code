#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m,a[N];
struct node{
	int s,lp,rp,tp,ln,rn,tn;
	int lpR,rpL,tpL,tpR,lnR,rnL,tnL,tnR;
	bool tag;
}tr[N<<2];
#define ls p<<1
#define rs p<<1|1
#define mid ((l+r)>>1)
void upd(node&p){
	p.s=-p.s,p.tag^=1;
	swap(p.lp,p.ln),swap(p.lpR,p.lnR),p.lp=-p.lp,p.ln=-p.ln;
	swap(p.rp,p.rn),swap(p.rpL,p.rnL),p.rp=-p.rp,p.rn=-p.rn;
	swap(p.tp,p.tn),swap(p.tpL,p.tnL),swap(p.tpR,p.tnR),p.tp=-p.tp,p.tn=-p.tn;
}
void push_up(node&p,node x,node y){
	p.s=x.s+y.s;
	p.lp=max(x.lp,x.s+y.lp),p.lpR=x.lp>=x.s+y.lp?x.lpR:y.lpR;
	p.rp=max(y.rp,y.s+x.rp),p.rpL=y.rp>=y.s+x.rp?y.rpL:x.rpL;
	p.tp=max({x.tp,y.tp,x.rp+y.lp});
	if(p.tp==x.tp) p.tpL=x.tpL,p.tpR=x.tpR;
	else if(p.tp==y.tp) p.tpL=y.tpL,p.tpR=y.tpR;
	else p.tpL=x.rpL,p.tpR=y.lpR;
	p.ln=min(x.ln,x.s+y.ln),p.lnR=x.ln<=x.s+y.ln?x.lnR:y.lnR;
	p.rn=min(y.rn,y.s+x.rn),p.rnL=y.rn<=y.s+x.rn?y.rnL:x.rnL;
	p.tn=min({x.tn,y.tn,x.rn+y.ln});
	if(p.tn==x.tn) p.tnL=x.tnL,p.tnR=x.tnR;
	else if(p.tn==y.tn) p.tnL=y.tnL,p.tnR=y.tnR;
	else p.tnL=x.rnL,p.tnR=y.lnR;
}
void build(int l,int r,int p){
	tr[p].tag=0;
	if(l==r){
		tr[p].s=tr[p].lp=tr[p].rp=tr[p].tp=tr[p].ln=tr[p].rn=tr[p].tn=a[l];
		tr[p].lpR=tr[p].rpL=tr[p].tpL=tr[p].tpR=tr[p].lnR=tr[p].rnL=tr[p].tnL=tr[p].tnR=l;
		return;
	}
    build(l,mid,ls),build(mid+1,r,rs);
	push_up(tr[p],tr[ls],tr[rs]);
}
void push_down(int p){
	if(!tr[p].tag)return ;
	upd(tr[p<<1]),upd(tr[p<<1|1]),tr[p].tag=0;
}
void update(int l,int r,int p,int s,int t){
    if(s<=l&&r<=t)
        return upd(tr[p]);
    push_down(p);
    if(s<=mid)update(l,mid,ls,s,t);
    if(t>mid)update(mid+1,r,rs,s,t);
    push_up(tr[p],tr[ls],tr[rs]);
}
signed main(){
    #ifndef LOCAL
        freopen("lis.in","r",stdin);
        freopen("lis.out","w",stdout);
    #endif
    ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	int sum=0;
	for(int i=1,x,y;i<=n;i++){
		cin>>x>>y;
		a[i]=x?-y:y;
		if(x)sum+=y;
	}
	cin>>m,build(1,n,1);
    int ans=sum+max(0LL,tr[1].lp);
    cout<<ans<<"\n";
	if(tr[1].lp>0)update(1,n,1,1,tr[1].lpR);
	while(m--){
		int v=max(0LL,tr[1].tp);
		cout<<(ans+=v)<<"\n";
		if(v)update(1,n,1,tr[1].tpL,tr[1].tpR);
	}
	return 0;
}