#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int n,q,bk,ans;
int a[N],b[N];
int ll[N],rr[N];
int id[N],Ans[N];
struct node{
    int l,r,id;
}qu[N];
void addr(int x){
    if(!ll[a[x]])ll[a[x]]=x;
    rr[a[x]]=x;
    ans=max(ans,rr[a[x]]-ll[a[x]]);
    return ;
}
void addl(int x){
    if(!rr[a[x]])rr[a[x]]=x;
    ans=max(ans,rr[a[x]]-x);
    return ;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n,bk=sqrt(n);
    for(int i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
    sort(b+1,b+n+1);
    int nn=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+nn+1,a[i])-b;
    for(int i=1;i<=n;i++)id[i]=(i-1)/bk+1;
    cin>>q;
    for(int i=1;i<=q;i++)cin>>qu[i].l>>qu[i].r,qu[i].id=i;
    sort(qu+1,qu+q+1,[](node A,node B){
        return id[A.l]==id[B.l]?A.r<B.r:A.l<B.l;
    });
    int j=1;
    for(int i=1;i<=id[n];i++){
        int l=i*bk+1,r=i*bk;
        ans=0;
        memset(ll,0,sizeof(ll));
        memset(rr,0,sizeof(rr));
        while(id[qu[j].l]==i&&j<=q){
            l=i*bk+1;
            node now=qu[j];
            if(id[now.l]==id[now.r]){
                int sum=0;
                for(int j=now.l;j<=now.r;j++){
                    if(!ll[a[j]])ll[a[j]]=j;
                    rr[a[j]]=j,sum=max(sum,rr[a[j]]-ll[a[j]]);
                }
                for(int j=now.l;j<=now.r;j++)
                    ll[a[j]]=rr[a[j]]=0;
                Ans[now.id]=sum,j++;
                continue;
            }
            while(r<now.r)addr(++r);
            int sum=ans;
            while(l>now.l)addl(--l);
            for(int k=now.l;k<=i*bk;k++)
                if(rr[a[k]]<=i*bk)
                    rr[a[k]]=0;
            Ans[now.id]=ans,ans=sum;
            j++;
        }
    }
    for(int i=1;i<=q;i++)cout<<Ans[i]<<"\n";
    return 0;
}