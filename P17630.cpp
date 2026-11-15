#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
using namespace std;
const int N=2e5+5,mod=200003,G=(20005>>6)+1;
int n,m,q,a[N];
int l[N],r[N];
basic_string<short>Q[N];
namespace READER{
	unsigned sd,z1,z2,z3,z4,Amax;
	unsigned rnd(){
		sd=((z1<<6)^z1)>>13,z1=((z1&4294967294U)<<18)^sd;
		sd=((z2<<2)^z2)>>27,z2=((z2&4294967288U)<<2)^sd;
		sd=((z3<<13)^z3)>>21,z3=((z3&4294967280U)<<7)^sd;
		sd=((z4<<3)^z4)>>12,z4=((z4&4294967168U)<<13)^sd;
		return (z1^z2^z3^z4);
	}
	void init(){
		cin>>n>>m>>q>>sd>>Amax;
		z1=sd,z2=(~sd)^0x233333333U; 
		z3=sd^0x1234598766U,z4=(~sd)+51;
		for(int i=1;i<=n;i++)
			a[i]=rnd()%Amax+1;
		for(int i=1;i<=m;i++){
			l[i]=rnd()%n+1,r[i]=rnd()%n+1;
			if(l[i]>r[i])swap(l[i],r[i]);
		}
		for(int i=1;i<=q;i++)
			Q[rnd()%n].push_back(rnd()%m);
	}
}
const ull S=-1;
ull ans=0,pr[G],c[G];
int inv[mod],cnt[N],t[G];
ull sum[40][G],Sum[40][G];
basic_string<int>v[N];
struct bit{
	ull c[G];
	inline void FAN(int x){
		for(int i=(x>>6);i<=m>>6;i++)c[i]^=S;
		if(x&63)--x,c[x>>6]^=((x&63)==63?S:((1ull<<(x&63)+1)-1ull));
	}
}b[mod],F;
inline void up(int x){
	int X=inv[x];
	for(int i=0,C=0;i<=m>>6;b[x].c[i]|=F.c[i],b[X].c[i]|=~F.c[i],++i){
		ull mod,p=(b[x].c[i]|F.c[i])^b[x].c[i]^(b[X].c[i]|~F.c[i])^b[X].c[i];
		c[i]+=C;if(!p)continue;C+=__builtin_popcountll(p);
		for(int j=0;p;p=mod,++j)mod=(p&sum[j][i]),sum[j][i]^=p;
	}
	for(int i=0;i<=m>>6;++i){
		ull p=0,o=0;pr[i]+=c[i];
		for(int j=0;j<17;++j)
			o=Sum[j][i]^sum[j][i]^p,
			p=(Sum[j][i]&sum[j][i])|((Sum[j][i]^sum[j][i])&p),
			Sum[j][i]=o;
		for(int j=17;p;++j)
			o=Sum[j][i]^p,p=Sum[j][i]&p,Sum[j][i]=o;
	}
}
inline ull ask(int x){
	ull res=pr[x>>6];
	for(int i=0;i<40;++i)res+=((ull)__builtin_popcountll(((x&63)==63)?Sum[i][x>>6]:(Sum[i][x>>6]&((1ull<<(x&63)+1)-1))))<<i;
	return res;
}
int qpow(int x,int y,int s=1){
	while(y){
		if(y&1)s*=x,s%=mod;
		x*=x,x%=mod,y>>=1;
	}return s;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	READER::init(),inv[1]=1;
	for(int i=2;i^mod;i++)inv[i]=(ll)(mod-mod/i)*inv[mod%i]%mod;
	for(int i=0;i^q;++i)
	for(int i=0;i^n;++i){
		for(int t:v[i])F.FAN(t);
		up(a[i]);
		for(int x:Q[i])ans^=ask(x);
	}
	cout<<ans;
}