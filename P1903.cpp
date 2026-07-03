#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
struct ques{
	int l,r,t,id;
}qu[N];
struct change{
	int x,y,t;
}ch[N];
int n,m,kc,nq,nc;
int l=1,r,t,Ans;
int ans[N],vis[N];
int a[N];
bool cmp(ques A,ques B){
    return A.l/kc!=B.l/kc?A.l<B.l:(A.r/kc==B.r/kc?A.t<B.t:A.r<B.r);
}
void add(int x){
	vis[x]++;
	if(vis[x]==1)Ans++;
}
void del(int x){
	vis[x]--;
	if(vis[x]==0)Ans--;
}
void update(int time,int x){
	if(qu[x].l<=ch[time].x&&ch[time].x<=qu[x].r)
		del(a[ch[time].x]),add(ch[time].y);
	swap(a[ch[time].x],ch[time].y);
}
void rd(int &x){
    char c=getchar_unlocked();x=0;
    while(c<'0'||c>'9')c=getchar_unlocked();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar_unlocked();
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	rd(n),rd(m);
	for(int i=1;i<=n;i++)rd(a[i]);
	for(int i=1;i<=m;i++){
        char op=getchar_unlocked();
        while(op!='Q'&&op!='R')op=getchar_unlocked();
		int A,B;rd(A),rd(B);
		if(op=='Q')nq++,qu[nq]={A,B,nc,nq};
		else nc++,ch[nc]={A,B,nc};
	}
    kc=pow(n,35.00/48.00);
	sort(qu+1,qu+nq+1,cmp);
	for(int i=1;i<=nq;i++){
		ques now=qu[i];
		while(l>now.l)add(a[--l]);
		while(l<now.l)del(a[l++]);
		while(r<now.r)add(a[++r]);
		while(r>now.r)del(a[r--]);
		while(t<now.t)update(++t,i);
		while(t>now.t)update(t--,i);
		ans[now.id]=Ans;
	}
	for(int i=1;i<=nq;i++)cout<<ans[i]<<"\n";
	return 0;
}