#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_cxx;
const int N=2e5+5;
int ans[N],n;
int tr[N];
rope<int>g;
inline int lowbit(int x){return x&-x;}
inline void update(int x,int val){
    while(x<=n)tr[x]=max(tr[x],val),x+=lowbit(x);
}
inline int query(int x,int s=0){
    while(x)s=max(s,tr[x]),x-=lowbit(x);
    return s;
}
inline void rd(int &x){
    char c=getchar();x=0;
    while(c>'9'||c<'0')c=getchar();
    while(c>='0'&&c<='9')
        x=x*10+c-'0',c=getchar();
}
void print(int x){
    if(x>9)print(x/10);
    putchar(x%10+'0');
}
signed main(){
    rd(n);
    for(int i=1,x;i<=n;i++)rd(x),x--,g.insert(+x,i);
    for(int i=0;i<n;i++)
        ans[g[i]]=query(g[i])+1,update(g[i],ans[g[i]]);
    for(int i=1;i<=n;i++)
        print(ans[i]=max(ans[i],ans[i-1])),puts("");
}