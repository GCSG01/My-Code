#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,S=700,C=S*2+5,M=N/S*2+10;
struct task{
    int a,b;
}p[N];
struct node{
    int len,tag,sum;
    int a[C];
}tr[M];
int n,bc,tot,id[M];
void push(int x){
    if(!tr[x].tag)return;
    for(int i=1;i<=tr[x].len;i++)
        tr[x].a[i]+=tr[x].tag;
    tr[x].tag=0;
}
void addall(int x,int v){
    tr[x].tag+=v,tr[x].sum+=v*tr[x].len;
}
void split_block(int k){
    int x=id[k],y=++tot,mid=tr[x].len/2;
    push(x);
    tr[y].len=tr[x].len-mid;
    tr[y].sum=tr[y].tag=0;
    for(int i=1;i<=tr[y].len;i++)
        tr[y].a[i]=tr[x].a[mid+i],tr[y].sum+=tr[y].a[i];
    tr[x].len=mid,tr[x].sum=0;
    for(int i=1;i<=mid;i++)
        tr[x].sum+=tr[x].a[i];
    for(int i=bc;i>=k+1;i--)id[i+1]=id[i];
    id[k+1]=y,bc++;
}
void insert_at(int k,int pos,int x){
    int y=id[k];
    push(y);
    for(int i=tr[y].len;i>=pos;i--)
        tr[y].a[i+1]=tr[y].a[i];
    tr[y].a[pos]=x;
    tr[y].sum+=x;
    tr[y].len++;
    if(tr[y].len>2*S)
        split_block(k);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    int ans=0;
    for(int i=1;i<=n;i++)
        cin>>p[i].a,ans+=p[i].a;
    for(int i=1;i<=n;i++)
        cin>>p[i].b;
    sort(p+1,p+n+1,[](task x,task y){return x.b>y.b;});
    int m=0;
    for(int z=1;z<=n;z++){
        int a=p[z].a,b=p[z].b;
        int pre=0,tb=0,loc=0;
        for(int k=1,st=1;k<=bc;k++){
            int x=id[k],r=st+tr[x].len-1;
            if(tr[x].a[tr[x].len]+tr[x].tag<=r*b-a){
                pre+=tr[x].len,st=r+1;
                continue;
            }
            for(int j=1;j<=tr[x].len;j++){
                if(tr[x].a[j]+tr[x].tag>(st+j-1)*b-a){
                    tb=k,loc=j;
                    break;
                }
            }
            break;
        }
        if(tb){
            int x=id[tb];
            push(x);
            for(int i=loc;i<=tr[x].len;i++)
                tr[x].a[i]+=b;
            tr[x].sum+=b*(tr[x].len-loc+1LL);
            for(int k=tb+1;k<=bc;k++)
                addall(id[k],b);
            insert_at(tb,loc,(pre+loc)*b-a);
        }
        else{
            if(!bc)id[bc=1]=++tot;
            insert_at(bc,tr[id[bc]].len+1,(m+1LL)*b-a);
        }
        m++;
    }
    int sum=0;
    for(int k=1;k<=bc;k++){
        int x=id[k];
        if(tr[x].a[tr[x].len]+tr[x].tag<0){
            sum+=tr[x].sum;
            continue;
        }
        push(x);
        for(int i=1;i<=tr[x].len;i++){
            if(tr[x].a[i]>=0)
                return cout<<ans+sum,0;
            sum+=tr[x].a[i];
        }
    }
    cout<<ans+sum;
}