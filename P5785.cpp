#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int n,S,t[N],c[N],b[N],f[N];
int tag[N<<2];
#define mid ((l+r)>>1)
#define ls p<<1
#define rs p<<1|1
int get(int x,int k){
	return -c[k]*x+S*(c[n]-c[k])+f[k];
}
void insert(int l,int r,int p,int k){
    if(l==r){
        if(get(b[l],k)<get(b[l],tag[p]))tag[p]=k;
        return ;
    }
    if(get(b[mid],k)<get(b[mid],tag[p]))swap(k,tag[p]);
	if(get(b[l],tag[p])>get(b[l],k))insert(l,mid,ls,k);
	if(get(b[r],tag[p])>get(b[r],k))insert(mid+1,r,rs,k);
}
int query(int l,int r,int p,int x){
    if(l==r)return get(b[x],tag[p]);
    int ans=get(b[x],tag[p]);
    if(x<=mid)return min(ans,query(l,mid,ls,x));
    return min(ans,query(mid+1,r,rs,x));
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>S;
	for(int i=1;i<=n;i++)
		cin>>t[i]>>c[i],t[i]+=t[i-1],c[i]+=c[i-1],b[i]=t[i];
	sort(b+1,b+n+1);
	int len=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)
		f[i]=query(1,len,1,lower_bound(b+1,b+len+1,t[i])-b)+t[i]*c[i],insert(1,len,1,i);
	cout<<f[n];
	return 0;
}