#include<bits/stdc++.h>
using namespace std;
const int N=1.5e5+5,M=3e5+5,B=1400;
int n,m,a[N];
int deg[N],tpn[N];
int Ans[B];
int q;
bool vis[N];
struct edge{
    int u,v;
}e[M];
struct node{
    int op,x,y;
}qu[B<<1|5];
vector<int>g[N];
bitset<B>f[N],c[N];
void rd(int &x){
    char ch=getchar();x=0;
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
}
void topo(){
    queue<int>que;
    for(int i=1;i<=n;i++)
        if(!deg[i])
            que.push(i);
    int tot=0;
    while(!que.empty()){
        int u=que.front();que.pop();
        tpn[++tot]=u;
        for(auto v:g[u])
            if(!--deg[v])
                que.push(v);
    }
}
void convolution(bitset<B>*p,int cnt){
    int res=0,k=n;
    memset(Ans,0,sizeof(Ans));
    while(k){
        int pt=0;
        for(int i=1;i+2<=k;i+=2){
            bitset<B>&x=p[i];
            bitset<B>&y=p[i+1];
            bitset<B>&z=p[i+2];
            bitset<B>t=x^y;
            p[++pt]=(x&y)|(t&z);
            z^=t;
        }
        if(k%2==0){
            bitset<B>t=p[k-1]^p[k];
            p[++pt]=p[k-1]&p[k];
            p[k]=t;
        }
        for(int i=0;i<cnt;i++)
            Ans[i]|=int(p[k][i])<<res;
        res++,k=pt;
    }
}
void solve(int q){
    for(int i=1;i<=n;i++)
        f[i].reset(),c[i].reset();
    vector<int>po;
    for(int i=1;i<=q;i++)
        if(qu[i].op==1&&!vis[qu[i].x])
            vis[qu[i].x]=1,po.push_back(qu[i].x);
    int cnt=0;
    for(int i=1;i<=q;i++)
        if(qu[i].op==2)
            f[qu[i].x][cnt++]=1;
    for(int i=1;i<=n;i++){
        int u=tpn[i];
        if(!vis[u])
            c[a[u]]|=f[u];
        for(auto v:g[u])
            f[v]|=f[u];
    }
    int id=0;
    for(int i=1;i<=q;i++){
        if(qu[i].op==1)
            a[qu[i].x]=qu[i].y;
        else{
            for(auto x:po)
                if(f[x][id])
                    c[a[x]][id]=1;
            id++;
        }
    }
    convolution(c,cnt);
    id=0;
    for(int i=1;i<=q;i++)
        if(qu[i].op==2)
            cout<<Ans[id++]<<"\n";
    for(auto x:po)vis[x]=0;
}
signed main(){
    ios::sync_with_stdio(0);
    rd(n),rd(m);
    for(int i=1;i<=n;i++)rd(a[i]);
    for(int i=1,u,v;i<=m;i++)
        rd(u),rd(v),g[u].push_back(v),deg[v]++;
    topo();
    int Q;rd(Q);
    int q1=0,q2=0;
    for(int i=1;i<=Q;i++){
        q++,rd(qu[q].op),rd(qu[q].x);
        if(qu[q].op==1)
            rd(qu[q].y),q1++;
        else q2++;
        if(q1==B||q2==B)
            solve(q),q=q1=q2=0;
    }
    if(q)solve(q);
}