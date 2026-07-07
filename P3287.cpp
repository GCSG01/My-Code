#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5,K=505;
int f[N][K];
int tr[N][K];
int a[N];
int n,k;
inline int lowbit(int x){return x&-x;}
void update(int x,int y,int v){
    while(x<=N-5){
        int yy=y;
        while(y<=k+1)tr[x][y]=max(tr[x][y],v),y+=lowbit(y);
        y=yy,x+=lowbit(x);
    }
    return ;
}
int query(int x,int y,int s=0){
    while(x){
        int yy=y;
        while(y)s=max(s,tr[x][y]),y-=lowbit(y);
        y=yy,x-=lowbit(x);
    }
    return s;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    f[1][0]=1;
    for(int i=1;i<=n;i++)
        for(int j=k;j>=0;j--){
            f[i][j]=query(a[i]+j,j+1)+1;
            update(a[i]+j,j+1,f[i][j]);
            // if(a[x]+y<=a[i]+j)
            // f[i][j]=max(f[i][j],f[x][y]+1);
        }
    cout<<query(N-5,k+1);
    return 0;
}