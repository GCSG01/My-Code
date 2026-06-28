#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
const int N=5e5+5;
struct node{
    int op,x,y,id;
}a[N*7];
int tmp[N*5];
int n,m;
int ans[N*4];
int tr[N*4];
inline int lowbit(int x){
    return x&-x;
}
void add(int x,int k){
    // cout<<"Add "<<x<<" "<<k<<"\n";
    while(x<=N-5)
        tr[x]+=k,x+=lowbit(x);
    return ;
}
int query(int x){
    // cout<<"query "<<x<<"\n";
    int s=0;
    while(x)
        s+=tr[x],x-=lowbit(x);
    return s;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    rd(n),rd(m);
    for(int i=1;i<=n;i++)
        rd(a[i].x),rd(a[i].y),a[i].op=2,tmp[i]=a[i].y;
    int nn=n;
    for(int i=1;i<=m;i++){
        int x,y,z,q;rd(x),rd(y),rd(z),rd(q);
        a[n+i]={1,z,q,i},
        a[n+m+i]={-1,x-1,q,i},
        a[n+m*2+i]={-1,z,y-1,i},
        a[n+m*3+i]={1,x-1,y-1,i};
        tmp[++nn]=q,tmp[++nn]=y-1;
    }
    sort(tmp+1,tmp+nn+1);
    nn=unique(tmp+1,tmp+nn+1)-tmp-1;
    sort(a+1,a+n+m*4+1,[](node A,node B){
        return A.x==B.x?A.op>B.op:A.x<B.x;
    });
    for(int i=1;i<=n+m*4;i++){
        a[i].y=lower_bound(tmp+1,tmp+nn+1,a[i].y)-tmp;
        if(a[i].op==2){
            add(a[i].y,1);
            continue;
        }
        ans[a[i].id]+=query(a[i].y)*a[i].op;
    }
    for(int i=1;i<=m;i++)
        cout<<ans[i]<<"\n";
    return 0;
}