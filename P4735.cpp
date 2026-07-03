#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
const int N=6e5+5,MX=1073741823;
int n,m;
int rt[N],tot;
int s[N];
struct node{
    int l,r,w;
}tr[N*30];
int ins(int x,int v,int l,int r){
    int p=++tot;tr[p]=tr[x];
    tr[p].w++;
    if(l==r)return p;
    int mid=(l+r)>>1;
    if(v<=mid)tr[p].l=ins(tr[x].l,v,l,mid);
    else tr[p].r=ins(tr[x].r,v,mid+1,r);
    return p;
}
int query(int x,int y,int l,int r,int v,int c){
    int sum=0,mid=(l+r)>>1;
    if(l==r)return l^v;
    if(((v>>(c))&1)==1){
        sum=tr[tr[y].l].w-tr[tr[x].l].w;
        if(sum>0)return query(tr[x].l,tr[y].l,l,mid,v,c-1);
        else return query(tr[x].r,tr[y].r,mid+1,r,v,c-1);
    }
    sum=tr[tr[y].r].w-tr[tr[x].r].w;
    if(sum>0)return query(tr[x].r,tr[y].r,mid+1,r,v,c-1);
    return query(tr[x].l,tr[y].l,l,mid,v,c-1);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    rt[0]=ins(0,0,0,MX);
    for(int i=1;i<=n;i++)cin>>s[i],s[i]^=s[i-1],rt[i]=ins(rt[i-1],s[i],0,MX);
    while(m--){
        char op;cin>>op;
        int l,r,x;
        if(op=='A'){
            cin>>x,n++;s[n]=s[n-1]^x;
            rt[n]=ins(rt[n-1],s[n],0,MX);
        }
        else{
            cin>>l>>r>>x,l--,r--;
            cout<<query(rt[l-1],rt[r],0,MX,x^s[n],29)<<"\n";
        }
    }
    return 0;
}