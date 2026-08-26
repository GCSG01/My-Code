#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5,mod=1e9+7,inv2=5e8+4;
int n,rt,tot;
struct node{
	int ls,rs;
	int day,more,ans;
}tr[N*35];
#define ls tr[p].ls
#define rs tr[p].rs
#define mid ((l+r)>>1)
int sum(int L,int R){
	return (L+R)%mod*((R-L+1)%mod)%mod*inv2%mod;
}
int f(int p,int l,int r,int x){
    if(!x)return tr[p].ans;
    if(l==r)return l%mod;
    if(tr[ls].day+x<=mid-l+1)
        return (f(ls,l,mid,x)+tr[p].ans-tr[ls].ans+mod)%mod;
    else return (sum(l,mid)+f(rs,mid+1,r,x-mid+l-1+tr[ls].day+tr[ls].more))%mod;
}
void push_up(int p,int l,int r){
    tr[p].day=tr[ls].day+min(tr[ls].more+tr[rs].day,r-mid);
    tr[p].more=tr[rs].more+max(0ll,tr[ls].more+tr[rs].day-r+mid);
    tr[p].ans=(tr[ls].ans+f(rs,mid+1,r,tr[ls].more))%mod;
    return ;
}
void update(int &p,int l,int r,int k,int v){
    if(!p)p=++tot;
    if(l==r){
        if(!v)tr[p].day=tr[p].more=tr[p].ans=0;
        else tr[p].day=1,tr[p].more=v-1,tr[p].ans=l%mod;
        return ;
    }
    if(k<=mid)update(ls,l,mid,k,v);
    else update(rs,mid+1,r,k,v);
    return push_up(p,l,r);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	while(n--){
        int x,y;cin>>x>>y;
		update(rt,1,2e14,x,y);
        cout<<tr[rt].ans<<"\n";
	}
	return 0;
}