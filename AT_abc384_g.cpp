#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    int f=1;
    while(c<'0'||c>'9'){
        if(c=='-'){f=-1;break;}
        c=getchar();
    }
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')
        x=x*10+c-'0',c=getchar();
    x=x*f;
}
const int N=3e5+5;
int n,k,bk;
int a[N],b[N];
int aa[N],bb[N];
int tmp[N],nn;
int Ans[N],ans;
struct ndq{
    int x,y,id;
}qu[N];
struct node{
    int tr[N];
    inline int lowbit(int x){return x&-x;}
    void update(int x,int k){
        while(x<=nn)tr[x]+=k,x+=lowbit(x);
    }
    int query(int x,int s=0){
        while(x)s+=tr[x],x-=lowbit(x);
        return s;
    }
    int get(int l,int r){
        return query(r)-query(l-1);
    }
}X,Y,sX,sY;
void adx(int x,int k){
    ans+=k*(sY.get(1,a[x])*aa[x]-Y.get(1,a[x]));
    ans+=k*(Y.get(a[x]+1,nn)-sY.get(a[x]+1,nn)*aa[x]);
    X.update(a[x],k*aa[x]),sX.update(a[x],k);
    return ;
}
void ady(int y,int k){
    ans+=k*(sX.get(1,b[y])*bb[y]-X.get(1,b[y]));
    ans+=k*(X.get(b[y]+1,nn)-sX.get(b[y]+1,nn)*bb[y]);
    Y.update(b[y],k*bb[y]),sY.update(b[y],k);
    return ;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],aa[i]=a[i],tmp[++nn]=a[i];
    for(int i=1;i<=n;i++)cin>>b[i],bb[i]=b[i],tmp[++nn]=b[i];
    sort(tmp+1,tmp+nn+1),nn=unique(tmp+1,tmp+nn+1)-tmp-1;
    for(int i=1;i<=n;i++)
        a[i]=lower_bound(tmp+1,tmp+nn+1,a[i])-tmp,
        b[i]=lower_bound(tmp+1,tmp+nn+1,b[i])-tmp;
    cin>>k,bk=sqrt(n);
    for(int i=1;i<=k;i++)cin>>qu[i].x>>qu[i].y,qu[i].id=i;
    sort(qu+1,qu+k+1,[](ndq A,ndq B){
        if(A.x/bk!=B.x/bk)return A.x<B.x;
        return (A.x/bk)&1?A.y<B.y:A.y>B.y;
    });
    int l=0,r=0;
    for(int i=1;i<=k;i++){
        while(l>qu[i].x)adx(l--,-1);
        while(r>qu[i].y)ady(r--,-1);
        while(l<qu[i].x)adx(++l,1);
        while(r<qu[i].y)ady(++r,1);
        Ans[qu[i].id]=ans;
    }
    for(int i=1;i<=k;i++)
        cout<<Ans[i]<<"\n";
    return 0;
}