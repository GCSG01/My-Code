#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=6e5+5;
int t1[N];
ll t2[N];
int n,m,q;
int l[N],r[N];
ll Ans[N];
struct node{
	int x,y,s,id;
}qu[N<<1];
struct Node{
	int y,x,s;
	ll b;
}op[N<<1];
inline int lowbit(int x){return x&-x;}
inline void add(int x,int s,ll b){
	while(x<=n)t1[x]+=s,t2[x]+=b,x+=lowbit(x);
}
inline void get(int x,int &s,ll &b){
	s=0,b=0;
	while(x)s+=t1[x],b+=t2[x],x-=lowbit(x);
}
inline ll calc(int x,int y){
	int s;ll b;
	get(x,s,b);
	return 1LL*y*s+b;
}
inline void rd(int &x){
    char c=getchar();x=0;
    while(c>'9'||c<'0')c=getchar();
    while(c>='0'&&c<='9')
        x=x*10+c-'0',c=getchar();
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	rd(n),rd(m),rd(q);
	for(int i=1;i<=n;i++)
		rd(l[i]),rd(r[i]),
		op[2*i-1]={l[i],i,1,1LL-l[i]},
		op[2*i]={r[i]+1,i,-1,1LL*r[i]};
	for(int i=1,a,b,c,d;i<=q;i++)
		rd(a),rd(b),rd(c),rd(d),
		qu[i*2-1]={d,b,1,i},qu[i*2]={d,a-1,-1,i},
		qu[q*2+i*2-1]={c-1,b,-1,i},
		qu[q*2+i*2]={c-1,a-1,1,i};
	sort(op+1,op+n*2+1,[](Node A,Node B){return A.y<B.y;});
	sort(qu+1,qu+q*4+1,[](node A,node B){return A.x<B.x;});
	int pos=1;
	for(int i=1;i<=q*4;i++){
		while(pos<=n*2&&op[pos].y<=qu[i].x)
			add(op[pos].x,op[pos].s,op[pos].b),pos++;
		Ans[qu[i].id]+=1LL*qu[i].s*calc(qu[i].y,qu[i].x);
	}
	for(int i=1;i<=q;i++)cout<<Ans[i]<<"\n";
}