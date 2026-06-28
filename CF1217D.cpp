#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
const int N=5e5+5;
int n,m;
vector<int>ed[N];
int in[N],vis[N];

int topo(){
    queue<int>q;
    for(int i=1;i<=n;i++)
        if(!in[i])
            q.push(i),vis[i]=1;
    while(!q.empty()){
        int u=q.front();q.pop();
        for(auto i:ed[u])
            if(!vis[i]){
                in[i]--;
                if(!in[i])
                    vis[i]=1,q.push(i);
            }
    }
    for(int i=1;i<=n;i++)
        if(!vis[i])return 0;
    return 1;
}
int col[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;cin>>u>>v;
        ed[u].push_back(v);
        in[v]++,col[i]=(u<v)+1;
    }
    if(topo()){
        cout<<"1\n";
        for(int i=1;i<=m;i++)
            cout<<"1 ";
        return 0;
    }
    cout<<"2\n";
    for(int i=1;i<=m;i++)
        cout<<col[i]<<" ";
    return 0;
}