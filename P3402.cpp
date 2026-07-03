#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_cxx;
const int N=2e5+5;
int n,m;
struct node{
    int x,siz;
};
rope<node>fa[N*15];
node find(int v,int x){
    node y=fa[v][x];
    if(y.x==x)return {x,y.siz};
    return find(v,y.x);
}
void merge(int v,int x,int y){
    auto a=find(v,x),b=find(v,y);
    if(a.siz>b.siz)
        swap(a,b),swap(x,y);
    auto &u=fa[v];
    u.replace(b.x,{b.x,u[b.x].siz+u[a.x].siz});
    u.replace(a.x,{b.x,0});
    return ;
}
bool check(int v,int x,int y){
    return find(v,x).x==find(v,y).x;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=0;i<=n;i++)
        fa[0].push_back({i,1});
    for(int i=1;i<=m;i++){
        int op,x,y;cin>>op>>x;
        if(op==1){
            cin>>y;
            fa[i]=fa[i-1];
            merge(i,x,y);
        }
        else if(op==2)
            fa[i]=fa[x];
        else{
            cin>>y,fa[i]=fa[i-1];
            cout<<check(i,x,y)<<"\n";
        }
    }
}