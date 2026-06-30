#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
namespace io {
	const int SI = 1 << 21 | 1;
	char IB[SI], *IS, *IT, OB[SI], *OS = OB, *OT = OS + SI - 1, c, ch[100];
	int f, t;
	#define gc() (IS == IT ? (IT = (IS = IB) + fread(IB, 1, SI, stdin), IS == IT ? EOF : *IS++) : *IS++)
	inline void flush() {
		fwrite(OB, 1, OS - OB, stdout), OS = OB;
	}
	inline void pc(char x) {
		*OS++ = x;
		if (OS == OT) flush();
	}
	template<class I>
	inline void rd(I &x) {
		for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;
		for (x = 0; c >= '0' && c <= '9'; x = (x << 3) + (x << 1) + (c & 15), c = gc());
		x *= f;
	}
	inline void rds(char *s, int &x) {
		for (c = gc(); c < 33 || c > 126; c = gc());
		for (x = 0; c >= 33 && c <= 126; s[++x] = c, c = gc());
		s[x+1] = '\0';
	}
	template<class I>
	inline void print(I x, char k = '\n') {
		if (!x) pc('0');
		if (x < 0) pc('-'), x = -x;
		while (x) ch[++t] = x % 10 + '0', x /= 10;
		while (t) pc(ch[t--]);
		pc(k);
	}
	inline void prints(string s) {
		int x = s.length();
		while (t < x) pc(s[t++]);
		pc('\n'), t = 0;
	}
	struct Flush {
		~Flush() {
			flush();
		}
	} flusher;
}
using io::rd;
using io::rds;
using io::print;
using io::prints;
int n,m,k;
int x[N],y[N];
int f[N],d[N];
struct node{
    int l,r;
    vector<int>e;
}tr[N<<2];
#define ls p<<1
#define rs p<<1|1
void build(int p,int l,int r){
    tr[p].l=l,tr[p].r=r;
    if(l==r)return ;
    int mid=(tr[p].l+tr[p].r)>>1;
    build(ls,l,mid),build(rs,mid+1,r);
    return ;
}
void insert(int p,int l,int r,int i){
    if(tr[p].l>=l&&tr[p].r<=r)
        return tr[p].e.push_back(i),void();
    int mid=(tr[p].l+tr[p].r)>>1;
    if(l<=mid)insert(ls,l,r,i);
    if(r>mid)insert(rs,l,r,i);
    return ;
}
inline int find(int x){
    while(x!=f[x])x=f[x];
    return x;
}
stack<pair<int,int>>st;
inline void merge(int x,int y){
    if(x==y)return ;
    if(d[x]>d[y])swap(x,y);
    st.push(make_pair(x,d[x]==d[y])),f[x]=y,d[y]+=(d[x]==d[y]);
    return ;
}
void dfs(int p,int l,int r){
    int flag=1,sz=st.size();
    for(int i:tr[p].e){
        int u=find(x[i]),v=find(y[i]);
        if(u==v){
            for(int j=l;j<=r;j++)prints("No");
            flag=0;break;
        }
        merge(find(x[i]+100005),v),merge(find(y[i]+100005),u);
    }
    if(flag){
        int mid=(tr[p].l+tr[p].r)>>1;
        if(l==r)prints("Yes");
        else dfs(ls,l,mid),dfs(rs,mid+1,r);
    }
    while(st.size()>sz)
        d[f[st.top().first]]-=st.top().second,f[st.top().first]=st.top().first,st.pop();
    return ;
}
int main(){
    // ios::sync_with_stdio(0);cin.tie(0);
    rd(n),rd(m),rd(k);
    build(1,1,k);
    for(int i=1,l,r;i<=m;i++){
        rd(x[i]),rd(y[i]),rd(l),rd(r);
        if(l^r)insert(1,l+1,r,i);
    }
    for(int i=1;i<=n;i++)f[i]=i,f[i+100005]=i+100005;
    dfs(1,1,k);
    return 0;
}