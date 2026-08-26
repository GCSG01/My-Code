#include<bits/stdc++.h>
//#define int long long
using namespace std;
const int inf=1e9,N=3e6+5;
int rub[N],cnt;
int tot;
struct tree{
	int ls,rs,pri,sz,val,l,r,sum,cnt[2],len[2],tgl[2],tgr[2];
}t[N];
unsigned seed=145874587;
inline unsigned rd(){
	seed^=seed<<13;
	seed^=seed>>17;
	seed^=seed<<5;
	return seed;
}
inline int New(int val,int l,int r){
	int c;
	if(cnt)c=rub[cnt--];
	else c=++tot;
	t[c].ls=t[c].rs=0,t[c].pri=rd(),t[c].sz=1;
	t[c].l=l,t[c].r=r,t[c].val=val;
	t[c].sum=val*(r-l+1);
	t[c].cnt[val]=1,t[c].cnt[!val]=0;
	t[c].len[val]=r-l+1,t[c].len[!val]=inf;
	t[c].tgl[0]=t[c].tgl[1]=t[c].tgr[0]=t[c].tgr[1]=0;
	return c;
}
inline void del(int c){
	if(!c)return;
	rub[++cnt]=c;
	del(t[c].ls),del(t[c].rs);
}
inline void upd(int c){
	tree&x=t[c],&l=t[x.ls],&r=t[x.rs];
	x.sz=l.sz+r.sz+1;
	x.sum=l.sum+r.sum+x.val*(x.r-x.l+1);
	x.cnt[0]=l.cnt[0]+r.cnt[0];
	x.cnt[1]=l.cnt[1]+r.cnt[1];
	x.cnt[x.val]++;
	x.len[0]=l.len[0]<r.len[0]?l.len[0]:r.len[0];
	x.len[1]=l.len[1]<r.len[1]?l.len[1]:r.len[1];
	if(x.r-x.l+1<x.len[x.val])x.len[x.val]=x.r-x.l+1;
}
inline void tag(int c,int val,int vl,int vr){
	if(!c)return;
	int d=vr-vl;
	t[c].sum+=val*t[c].cnt[val]*d;
	t[c].len[val]+=d;
	if(t[c].val==val)t[c].l+=vl,t[c].r+=vr;
	t[c].tgl[val]+=vl,t[c].tgr[val]+=vr;
}
inline void down(int c){
	if(t[c].tgl[0]||t[c].tgr[0]){
		tag(t[c].ls,0,t[c].tgl[0],t[c].tgr[0]);
		tag(t[c].rs,0,t[c].tgl[0],t[c].tgr[0]);
		t[c].tgl[0]=t[c].tgr[0]=0;
	}
	if(t[c].tgl[1]||t[c].tgr[1]){
		tag(t[c].ls,1,t[c].tgl[1],t[c].tgr[1]);
		tag(t[c].rs,1,t[c].tgl[1],t[c].tgr[1]);
		t[c].tgl[1]=t[c].tgr[1]=0;
	}
}
inline int merge(int x,int y){
	if(!x||!y)return x|y;
	if(t[x].pri>t[y].pri){
		down(x);
		t[x].rs=merge(t[x].rs,y);
		upd(x);
		return x;
	}
	down(y);
	t[y].ls=merge(x,t[y].ls);
	upd(y);
	return y;
}
inline void split_ol(int c,int&x,int&y){
	if(!c)return x=y=0,void();
	down(c);
	if(!t[c].ls)x=c,y=t[c].rs,t[c].rs=0;
	else y=c,split_ol(t[c].ls,x,t[c].ls);
	upd(c);
}
inline void split_or(int c,int&x,int&y){
	if(!c)return x=y=0,void();
	down(c);
	if(!t[c].rs)y=c,x=t[c].ls,t[c].ls=0;
	else x=c,split_or(t[c].rs,t[c].rs,y);
	upd(c);
}
inline int assign(int x,int y){
	if(!x||!y)return x|y;
	int a,b,c,d;
	split_or(x,a,b),split_ol(y,c,d);
	if(t[b].val==t[c].val){
		t[b].r=t[c].r;
		rub[++cnt]=c;
		upd(b);
		return merge(merge(a,b),d);
	}
	return merge(merge(a,b),merge(c,d));
}
inline void split_rk(int c,int k,int&x,int&y){
	if(!c)return x=y=0,void();
	down(c);
	if(k<t[c].l){
		y=c;
		split_rk(t[c].ls,k,x,t[c].ls);
		upd(y);
		return;
	}
	if(k>=t[c].r){
		x=c;
		split_rk(t[c].rs,k,t[c].rs,y);
		upd(x);
		return;
	}
	y=New(t[c].val,k+1,t[c].r);
	t[y].rs=t[c].rs;
	x=c;
	t[x].r=k,t[x].rs=0;
	upd(x),upd(y);
}
inline void split_le(int c,int k,int&x,int&y){
	if(!c)return x=y=0,void();
	down(c);
	if(t[c].l<=k)x=c,split_le(t[c].rs,k,t[c].rs,y);
	else y=c,split_le(t[c].ls,k,x,t[c].ls);
	upd(c);
}
inline void split_ri(int c,int k,int&x,int&y){
	if(!c)return x=y=0,void();
	down(c);
	if(t[c].r<=k)x=c,split_ri(t[c].rs,k,t[c].rs,y);
	else y=c,split_ri(t[c].ls,k,x,t[c].ls);
	upd(c);
}
int rt;
int rebuild(int c){
	if(!c||(t[c].len[0]>0&&t[c].len[1]>0))return c;
	down(c);
	t[c].ls=rebuild(t[c].ls),t[c].rs=rebuild(t[c].rs);
	if(t[c].r-t[c].l+1<=0){
		rub[++cnt]=c;
		return assign(t[c].ls,t[c].rs);
	}
	if(t[c].ls){
		int x,y;split_or(t[c].ls,x,y);
		if(t[y].val==t[c].val){
			t[c].l=t[y].l;
			rub[++cnt]=y;
			t[c].ls=x;
		}
		else t[c].ls=merge(x,y);
	}
	if(t[c].rs){
		int x,y;split_ol(t[c].rs,x,y);
		if(t[x].val==t[c].val){
			t[c].r=t[x].r;
			rub[++cnt]=x;
			t[c].rs=y;
		}
		else t[c].rs=merge(x,y);
	}
	upd(c);
	return c;
}
inline void cover(int l,int r,int val){
	int x,y,z;
	split_rk(rt,l-1,x,y),split_rk(y,r,y,z);
	del(y);
	y=New(val,l,r);
	rt=assign(assign(x,y),z);
}
inline void addl(int l,int r,int val,int k){
	if(l>r)return;
	int x,y,z;
	split_le(rt,l-1,x,y),split_le(y,r,y,z);
	tag(y,val,k,0);
	rt=merge(merge(x,y),z);
}
inline void addr(int l,int r,int val,int k){
	if(l>r)return;
	int x,y,z;
	split_ri(rt,l-1,x,y),split_ri(y,r,y,z);
	tag(y,val,0,k);
	rt=merge(merge(x,y),z);
}
inline int sum(int l,int r){
	int x,y,z;
	split_rk(rt,l-1,x,y),split_rk(y,r,y,z);
	int ans=t[y].sum;
	rt=assign(assign(x,y),z);
	return ans;
}
int n,m,a[N];
pair<int,int>seg[N];
int cseg;
int build(int l,int r){
    if(l>r)return 0;
    int d=(l+r)>>1;
    int ls=build(l,d-1),rs=build(d+1,r),c=New(a[seg[d].first],seg[d].first,seg[d].second);
    t[c].ls=ls,t[c].rs=rs;
    upd(c);
    return c;
}
namespace IO
{
	int len=0;
	char ibuf[(1<<20)+1],*iS,*iT,out[(1<<26)+1];
	#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
	#define reg register
	inline int read()
	{
		reg char ch=gh();
		reg int x=0;
		reg char t=0;
		while(ch<'0'||ch>'9')ch=gh();
		while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
		return t?-x:x;
	}
	inline void putc(char ch)
	{
		out[len++]=ch;
	}
	template<class T>
	inline void write(T x)
	{
		if(x<0)putc('-'),x=-x;
		if(x>9)write(x/10);
		out[len++]=x%10+48;
	}
	inline void flush()
	{
		fwrite(out,1,len,stdout);
		len=0;
	}
}
using IO::read;
using IO::write;
using IO::flush;
using IO::putc;
signed main(){
	t[0].len[0]=t[0].len[1]=inf;
	n=read(),m=read();
	for(register int i=1;i<=n;i++)a[i]=read();
	a[n+1]=-1;
	register int lst=0;
	for(register int i=1;i<=n;i++)if(a[i]!=a[i+1])seg[++cseg]={lst+1,i},lst=i;
    rt=build(1,cseg);
	lst=0;
	while(m--){
		register int op=read(),l=read(),r=read();
		l^=lst,r^=lst;
		if(op<=2)cover(l,r,op-1);
		if(op==3){
			addl(l+1,r,1,-1);
			addr(l,r-1,0,-1);
			rt=rebuild(rt);
		}
		if(op==4){
			addr(l,r-1,1,1);
			addl(l+1,r,0,1);
			rt=rebuild(rt);
		}
		if(op==5){
			addl(l+1,r,0,-1);
			addr(l,r-1,1,-1);
			rt=rebuild(rt);
		}
		if(op==6){
			addr(l,r-1,0,1);
			addl(l+1,r,1,1);
			rt=rebuild(rt);
		}
		if(op==7)write(lst=sum(l,r)),putc('\n');
	}
    return flush(),0;
}