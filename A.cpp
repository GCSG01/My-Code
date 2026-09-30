#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n;
int a[N];
struct BIT{
    int t[N];
    inline void add(int x){
        while(x<=n)t[x]++,x+=x&-x;
    }
    inline int ask(int x){
        int r=0;
        while(x)r+=t[x],x-=x&-x;
        return r;
    }
    inline void clear(){
        memset(t,0,(n+2)*sizeof(int));
    }
}bit;
struct Seg{
    int mx[N<<2],tag[N<<2];
    inline void add(int p,int v){
        mx[p]+=v,tag[p]+=v;
    }
    inline void push(int p){
        if(!tag[p])return ;
		add(p<<1,tag[p]);
		add(p<<1|1,tag[p]);
		tag[p]=0;
    }
    void modify(int p,int l,int r,int L,int R,int v){
        if(L<=l&&r<=R)
            return add(p,v),void();
        push(p);
        int mid=(l+r)>>1;
        if(L<=mid)modify(p<<1,l,mid,L,R,v);
        if(R>mid)modify(p<<1|1,mid+1,r,L,R,v);
        mx[p]=max(mx[p<<1],mx[p<<1|1]);
    }
}seg;
struct node{
    int x,l,r,v;
}e[N<<1];
int pre[N],suf[N];
int main(){
	freopen("essenceoftwilight.in","r",stdin);
	freopen("essenceoftwilight.out","w",stdout);
    ios::sync_with_stdio(0);cin.tie(0);
    int T,C;cin>>T>>C;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        long long inv=0;
        bit.clear();
        for(int i=n;i;i--)
            inv+=bit.ask(a[i]-1),bit.add(a[i]);
        int pc=0,mx=0;
        for(int i=1;i<=n;i++)
            if(a[i]>mx)
                mx=a[i],pre[++pc]=i;
        int sc=0,mn=n+1;
        for(int i=n;i;i--)
            if(a[i]<mn)
                mn=a[i],suf[++sc]=i;
        int cnt=0;
        for(int k=1;k<=n;k++){
            int l=1,r=0,L=0,R=pc;
            while(L<R){
                int mid=(L+R+1)>>1;
                if(pre[mid]<k&&a[pre[mid]]<a[k])L=mid;
                else R=mid-1;
            }
            int left=L+1;
            L=0,R=sc;
            while(L<R){
                int mid=(L+R+1)>>1;
                if(suf[mid]<k)L=mid;
                else R=mid-1;
            }
            int rightStart=L+1;
            if(left>pc||rightStart>sc)continue;
            e[++cnt]={left,rightStart,sc,2};
            e[++cnt]={pc+1,rightStart,sc,-2};
        }
        sort(e+1,e+cnt+1,[](node A,node B){return A.x<B.x;});
        int best=0,now=1;
        for(int i=1;i<=pc;i++){
            while(now<=cnt&&e[now].x==i)
                seg.modify(1,1,sc,e[now].l,e[now].r,e[now].v),now++;
            best=max(best,seg.mx[1]);
        }
        cout<<max(0ll,inv-best-1)<<"\n";
    }
}