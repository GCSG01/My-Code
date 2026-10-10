#include<bits/stdc++.h>
using namespace std;
const int inf=0x7fffffff/2,N=5e3+5;
int n;
int cnt[N];
bitset<N>vis;
double dis[N];
struct node{
    int t,c;
    double k,w;
};
vector<node>g[N];
void add(int f,int t,double w,int c,double k){
    g[f].push_back({t,c,k,w});
}
bool spfa(double num){
    queue<int>q;
    for(int i=0;i<=n+1;i++)dis[i]=-inf,vis[i]=cnt[i]=0;
    q.push(n+1);
    dis[n+1]=0,vis[n+1]=cnt[n+1]=1;
    while(!q.empty()){
        int u=q.front();
        q.pop(),vis[u]=0;
        for(auto e:g[u]){
            int v=e.t;
            double w;
            if(e.c==0)w=e.w;
            if(e.c==1)w=log2(e.k-num);
            if(e.c==2)w=-log2(e.k+num);
            if(dis[v]<dis[u]+w){
                dis[v]=dis[u]+w;
                if(!vis[v]){
                    q.push(v),vis[v]=1;
                    if(++cnt[v]>=n+1)return false;
                }
            }
        }
    }
    return true;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int s,t;cin>>n>>s>>t;
    double l=0,r=10;
    for(int i=1,o,A,B,K;i<=s;i++){
        double k;cin>>o>>A>>B>>k;
        add(B,A,0,o,k);
        if(o==1)r=min(r,k);
    }
    for(int i=1,C;i<=t;i++){
        double x;cin>>C>>x;
        add(0,C,log2(x),0,0),
        add(C,0,-log2(x),0,0);
    }
    for(int i=0;i<=n;i++)add(n+1,i,0,0,0);
    if(spfa(0))return cout<<-1,0;
    while(r-l>1e-5){
        double mid=(l+r)/2;
        if(spfa(mid))r=mid;
        else l=mid;
    }
    cout<<l;
}