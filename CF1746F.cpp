#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5,inf=0x3f3f3f3f;
void read(int &x){
    int f=0;x=0;
    char ch=getchar();
	while(ch<'0'||ch>'9')
        f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')
    x=x*10+ch-48,ch=getchar();
	x=f?-x:x;
}
int n,q,a[N],b[N];
int op[N],l[N],r[N],k[N];
int num[N],ntot;
int val[N];
int ans[N];
int tr[N];
#define lowbit(x)(x&-x)
void update(int x,int v){
    while(x<=n)
    tr[x]+=v,x+=lowbit(x);
	return;
}
int query(int x,int sum=0){
    while(x)
    sum+=tr[x],x-=lowbit(x);
	return sum;
}
int get(int l,int r){
    return query(r)-query(l-1);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    mt19937 rnd(time(0));
	read(n),read(q);
	for(int i=1;i<=n;i++)
        read(a[i]),num[++ntot]=a[i];
	for(int i=1;i<=q;i++){
		read(op[i]),read(l[i]),read(r[i]),ans[i]=1;
		if(op[i]==2)read(k[i]);
		else num[++ntot]=r[i];
	}
	sort(num+1,num+ntot+1);
	ntot=unique(num+1,num+ntot+1)-num-1;
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(num+1,num+ntot+1,a[i])-num;
	for(int i=1;i<=q;i++)
		if(op[i]==1)
			r[i]=lower_bound(num+1,num+ntot+1,r[i])-num;
	for(int T=1;T<=30;T++){
		memset(tr,0,sizeof(tr));
		memcpy(b,a,sizeof(b));
		for(int i=1;i<=ntot;i++)
			val[i]=rnd()/2;
		for(int i=1;i<=n;i++)
			update(i,val[b[i]]);
		for(int i=1;i<=q;i++)
			if(op[i]==1)
				update(l[i],val[r[i]]-val[b[l[i]]]),b[l[i]]=r[i];
			else if(ans[i]){
                if((r[i]-l[i]+1)%k[i])
                    ans[i]=0;
                else if(get(l[i],r[i])%k[i])
                    ans[i]=0;
            }
	}
	for(int i=1;i<=q;i++)
		if(op[i]==2)
            cout<<(ans[i]?"YES":"NO")<<"\n";
	return 0;
}