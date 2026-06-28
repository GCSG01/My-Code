#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
bool f[20000000];
int phi[20000000];
vector<int>pr;
int a[N],tr[N];
int n,m;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c<='9'&&c>='0')x=x*10+c-'0',c=getchar();
}
void init(){
    phi[1]=1;
    for(int i=2;i<=20000000;i++){
        if(!f[i])pr.push_back(i),phi[i]=i-1;
        for(int j:pr){
            if(i*j>20000000)break;
            f[i*j]=1;
            if(i%j)phi[i*j]=phi[i]*(j-1);
            else{
                phi[i*j]=phi[i]*j;
                break;
            }
        }
    }
    return ;
}
#define lowbit(x) x&-x
void add(int x,int v){
    while(x<=n)tr[x]+=v,x+=lowbit(x);
    return ;
}
int query(int x,int s=0){
    while(x)s+=tr[x],x-=lowbit(x);
    return s;
}
struct node{
    int val;
    bool flag;
    node(int val=0,bool flag=0):val(val),flag(flag){}
};
node power(int x,int y,int p){
    node res=node(1,0);
    if(x>=p)x%=p,res.flag=1;
    // cout<<x<<"^"<<y<<"= ";
    while(y){
        if(y&1)res.val=res.val*x;
        if(res.val>=p)
            res.flag=1,res.val%=p;
        y>>=1;
        if(y==0)break;
        x=x*x;
        if(x>=p)res.flag=1,x%=p;
    }
    // cout<<res.val<<"\n";
    return res;
}
node get(int l,int r,int p){
    node res;
    // cout<<l<<" "<<r<<" "<<p<<": ";
    int ll=query(l);
    // cout<<ll<<"\n";
    if(p<=1)return node(0,1); 
    if(ll==1)return node(1,0);
    if(l==r)return node(ll%p,(ll>=p));
    res=get(l+1,r,phi[p]);
    if(res.flag)res.val+=phi[p];
    return power(ll,res.val,p); 
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    rd(n),rd(m);
    init();
    for(int i=1;i<=n;i++)rd(a[i]),add(i,a[i]),add(i+1,-a[i]);
    // for(int i=1;i<=10;i++)cout<<phi[i]<<" ";cout<<"\n";
    while(m--){
        int op,l,r,x;rd(op),rd(l),rd(r),rd(x);
        if(op==1)add(l,x),add(r+1,-x);
        else cout<<get(l,r,x).val<<"\n";
    }
    return 0;
}