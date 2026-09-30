#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5;
void print(int x){
    if(x>9)print(x/10);
    putchar(x%10+'0');
}
inline void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')
        x=x*10+c-'0',c=getchar();
}
int n,m;
bitset<N>f;
struct node{
    int u,v,w;
}e[N];
int fa[N],siz[N];
int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
inline void merge(int x,int y){
    x=find(x),y=find(y);
    if(x==y)return ;
    if(siz[x]<siz[y])swap(x,y);
    fa[y]=x,siz[x]+=siz[y];
}
bool check(int x){
    for(int i=1;i<=n;i++)fa[i]=i;
    int cnt=0;
    for(int i=1;i<=m;i++){
        auto [u,v,w]=e[i];
        if(w==x||find(u)==find(v))continue;
        cnt++,merge(u,v);
        if(cnt==n-1)return true;
    }
    return false;
}
signed main(){
    rd(n),rd(m);
    for(int i=1,u,v,w;i<=m;i++)
        rd(u),rd(v),rd(w),e[i]={u,v,w};
    sort(e+1,e+m+1,[](node A,node B){return A.w<B.w;});
    int l=0,r=1e5+5,ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid))r=mid-1,ans=mid;
        else l=mid+1;
    }
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=m;i++){
        auto [u,v,w]=e[i];
        if(ans==w||find(u)==find(v))continue;
        merge(u,v),f[w]=1;
    }
    int cnt=0;
    while(f[cnt])cnt++;
    print(min(cnt,ans));
}