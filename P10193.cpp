#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e4+5;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
int n,m,c,r,k;
struct node{
    int v,w;
};
vector<node>a[N];
map<int,bool>f[N];
struct Node{
    int v,dis,fro;
};
bool operator<(const Node &A,const Node &B){
    return A.dis>B.dis;
}
void Dij(){
    priority_queue<Node>q;
    for(int i=1;i<=c;i++)
        q.push({i,0,i});
    while(!q.empty()){
        int x=q.top().v,d=q.top().dis,fro=q.top().fro;
        q.pop();
        if(f[x].count(fro)||(int)f[x].size()>=k)continue;
        f[x][fro]=1;
        for(auto y:a[x])
            if(d+y.w<=r&&(int)f[y.v].size()<k&&!f[y.v].count(fro))
                q.push({y.v,d+y.w,fro});
    }
    return ;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    rd(n),rd(m),rd(c),rd(r),rd(k);
    for(int i=1,u,v,w;i<=m;i++)
        rd(u),rd(v),rd(w),
        a[u].push_back({v,w}),
        a[v].push_back({u,w});
    Dij();
    vector<int>ans;
    for(int i=c+1;i<=n;i++)
        if((int)f[i].size()>=k)ans.push_back(i);
    cout<<ans.size();
    for(int i:ans)cout<<"\n"<<i;
    return 0;
}