#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+5;
int n,m,nn,S;
struct node{
    char op;int x,y;
}q[N];
int a[N],A[N];
int trv[N],trs[N];
inline int lowbit(int x){return x&-x;}
void update_val(int x,int k){
    if(x)while(x<=nn)trv[x]+=k,x+=lowbit(x);
}
void update_sum(int x,int k){
    if(x){
        S+=k;while(x<=nn)trs[x]+=k,x+=lowbit(x);
    }
}
int query_val(int x,int s=0){
    while(x>0)s+=trv[x],x-=lowbit(x);
    return s;
}
int query_sum(int x,int s=0){
    while(x>0)s+=trs[x],x-=lowbit(x);
    return s;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++)
        cin>>q[i].op>>q[i].x>>q[i].y,a[i]=q[i].y;
    sort(a+1,a+m+1);
    nn=unique(a+1,a+m+1)-a-1;
    for(int i=1;i<=m;i++)q[i].y=lower_bound(a+1,a+nn+1,q[i].y)-a;
    for(int i=1;i<=m;i++){
        int x=q[i].x,y=q[i].y;
        if(q[i].op=='U'){
            update_val(A[x],-a[A[x]]),update_sum(A[x],-1),A[x]=y;
            update_val(A[x],a[A[x]]),update_sum(A[x],1);
        }
        else{
            int sum=(S-query_sum(y))*a[y]+query_val(y);
            if(sum>=x*a[y])cout<<"TAK\n";
            else cout<<"NIE\n";
        }
    }
    return 0;
}