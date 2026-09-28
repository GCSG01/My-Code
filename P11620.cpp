#include<bits/stdc++.h>
using namespace std;
const int N=5e4+5,T=64,LG=30;
int n,m,b[N];
int tr[N],rt[T][N];
unsigned long long mask[N];
mt19937_64 rng(random_device{}());
inline int lowbit(int x){return x&-x;}
inline void add(int *tr,int x,int v){
    while(x<=n)
        tr[x]^=v,x+=lowbit(x);
}
inline int get(int *tr,int x,int s=0){
    while(x)
        s^=tr[x],x-=lowbit(x);
    return s;
}
int bit[LG+1];
inline void insert(int x){
    for(int i=LG;i>=0;i--){
        if(!(x>>i&1))continue;
        if(!bit[i])
            return bit[i]=x,void();
        x^=bit[i];
    }
}
inline int query(int x){
    for(int i=LG;i>=0;i--)
        x=max(x,x^bit[i]);
    return x;
}
void update(int x,int v){
    add(tr,x,v);
    if(x==1)return;
    for(int i=0;i<T;i++)
        if(mask[x]>>i&1)
            add(rt[i],x,v);
}
int query(int l,int r,int x){
    int a=get(tr,l);
    if(l==r)return max(x,x^a);
    memset(bit,0,sizeof(bit));
    for(int i=0;i<T;i++)
        insert(get(rt[i],r)^get(rt[i],l));
    return max(query(x),query(x^a));
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    int lst=0,x;
    for(int i=1;i<=n;i++)
        cin>>x,b[i]=lst^x,lst=x;
    for(int i=1;i<=n;i++){
        tr[i]^=b[i];
        if(i+lowbit(i)<=n)
            tr[i+lowbit(i)]^=tr[i];
    }
    for(int i=1;i<=n;i++)mask[i]=rng();
    for(int t=0;t<T;t++){
        for(int i=2;i<=n;i++)
            if(mask[i]>>t&1)
                rt[t][i]=b[i];
        for(int i=1;i<=n;i++)
            if(i+lowbit(i)<=n)
                rt[t][i+lowbit(i)]^=rt[t][i];
    }
    while(m--){
        int op,l,r,v;cin>>op>>l>>r>>v;
        if(op==1){
            update(l,v);
            if(r<n)update(r+1,v);
        }
        else cout<<query(l,r,v)<<"\n";
    }
}