#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
int n,m,siz;
int a[N];
int tr[N];
int Ans[N];
int b[N];
struct node{
    int op,l,r,k,x,y,id;
}q[N],q1[N],q2[N];
inline int lowbit(int x){
    return x&-x;
}
void add(int x,int k){
    while(x<=siz)
        tr[x]+=k,x+=lowbit(x);
    return ;
}
int query(int x,int s=0){
    while(x)s+=tr[x],x-=lowbit(x);
    return s;
}
void solve(int l,int r,int ql,int qr){
    if(ql>qr)return ;
    if(l==r){
        for(int i=ql;i<=qr;i++)
            if(q[i].op==2)
                Ans[q[i].id]=l;
        return ;
    }
    int mid=(l+r)>>1,ll=0,rr=0;
    for(int i=ql;i<=qr;i++){
        if(!q[i].op){
            if(q[i].y<=mid)
                q1[++ll]=q[i],add(q[i].x,1);
            else q2[++rr]=q[i];
        }
        else if(q[i].op==1){
            if(q[i].y<=mid)
                q1[++ll]=q[i],add(q[i].x,-1);
            else q2[++rr]=q[i];
        }
        else{
            int nw=query(q[i].r)-query(q[i].l-1);
            if(nw>=q[i].k)q1[++ll]=q[i];
            else q2[++rr]=q[i],q2[rr].k-=nw;
        }
    }
    for(int i=ql;i<=qr;i++)
        if(!q[i].op&&q[i].y<=mid)add(q[i].x,-1);
        else if(q[i].op==1&&q[i].y<=mid)add(q[i].x,1);
    int i=ql;
    for(int j=1;j<=ll;j++,i++)
        q[i]=q1[j];
    for(int j=1;j<=rr;j++,i++)
        q[i]=q2[j];
    solve(l,mid,ql,ql+ll-1);
    solve(mid+1,r,ql+ll,qr);
    return ;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    int tot=0;
    for(int i=1;i<=n;i++)
        cin>>a[i],b[++siz]=a[i],tot++,
        q[tot].id=tot,q[tot].op=0,q[tot].x=i,q[tot].y=a[i];
    int qu=0;
    // q[++tot]={2,1,1,1,1,1,++qu};
    for(int i=1;i<=m;i++){
        char op;int l,r,k;
        cin>>op>>l>>r;
        if(op=='Q'){
            cin>>k,tot++;
            q[tot]={2,l,r,k,0,0,++qu};
        }
        else{
            b[++siz]=r;
            q[++tot]={1,0,0,0,l,a[l],0};
            q[++tot]={0,0,0,0,l,r,0};
            a[l]=r;
        }
    }
    sort(b+1,b+siz+1);
    siz=unique(b+1,b+siz+1)-b-1;
    for(int i=1;i<=tot;i++)
        if(q[i].op==1||!q[i].op)
            q[i].y=lower_bound(b+1,b+siz+1,q[i].y)-b;
    solve(1,siz,1,tot);
    for(int i=1;i<=qu;i++)
        cout<<b[Ans[i]]<<"\n";
    return 0;
}