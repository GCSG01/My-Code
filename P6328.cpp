#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
vector<int>e[N];
int dis[N][N];
bitset<N>a[N][N];
int qu[N];
int n,m,q;
void bfs(int s){
    int l,r;l=r=1;
    qu[l]=s;
    for(int i=1;i<=n;i++)dis[s][i]=n+1;
    dis[s][s]=0;
    while(l<=r){
        int u=qu[l++];
        for(int v:e[u])
            if(dis[s][v]>n)
                dis[s][v]=dis[s][u]+1,qu[++r]=v;
    }
    for(int i=1;i<=n;i++)a[s][dis[s][i]][i]=1;
    for(int i=1;i<=n;i++)a[s][i]|=a[s][i-1];
    return ;
}
void rd(int &x){
    char c=getchar_unlocked();x=0;
    while(c<'0'||c>'9')c=getchar_unlocked();
    while(c<='9'&&c>='0')x=x*10+c-'0',c=getchar_unlocked();
}
void write(int x)
{
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    rd(n),rd(m),rd(q);
    for(int i=1;i<=m;i++){
        int u,v;rd(u),rd(v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for(int i=1;i<=n;i++)bfs(i);
    while(q--){
        int k;rd(k);
        bitset<N>tmp;
        for(int i=1,x,y;i<=k;i++)
            rd(x),rd(y),tmp|=a[x][y>n?n:y];
        write(tmp.count());
        puts("");
    }
    return 0;
}