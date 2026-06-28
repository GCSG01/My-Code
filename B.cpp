#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
const int N=5e5+5;
int n;
int a[3][N],b[3][N];
int pos[N];
int tr[N];
inline int lowbit(int x){
    return x&-x;
}
void add(int x){
    while(x<=n)
        tr[x]++,x+=lowbit(x);
    return ;
}
int query(int x,int s=0){
    while(x)
        s+=tr[x],x-=lowbit(x);
    return s;
}
signed main(){
    freopen("rotate.in","r",stdin);
    freopen("rotate.out","w",stdout);
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[1][i];
    for(int i=1;i<=n;i++)cin>>a[2][i];
    for(int i=1;i<=n;i++)cin>>b[1][i];
    for(int i=1;i<=n;i++)cin>>b[2][i];
    for(int i=1;i<=n;i++)
        pos[b[1][i]]=pos[b[2][i]]=i;
    int ans=0;
    for(int i=1;i<=n;i++){
        int x=a[1][i],y=a[2][i];
        if(pos[x]!=pos[y])
            return cout<<-1,0;
        if((abs(i-pos[x])%2)!=(x!=b[1][pos[x]]))
            return cout<<-1,0;
        ans+=i-query(pos[x])-1;
        add(pos[x]);
    }
    cout<<ans;
    return 0;
}