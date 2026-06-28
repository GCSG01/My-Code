#include<bits/stdc++.h>
#define pq priority_queue<int>
using namespace std;
const int N=2e5+5,inf=1e9+7;
vector<int>g[N];
bool vis[N],flag[N];
int fa[N],siz[N],que[N];
int dis[N][18],deep[N];
int nowdep,tot,root,lstans[N];
int get(pq& q,pq& del){
    while(!q.empty()&&(!del.empty()&&q.top()==del.top()))q.pop(),del.pop();
    return q.empty()?-inf:q.top();
}
void remove(pq& q,pq& del,int num){
    if(!q.empty()&&q.top()==num)q.pop();
    else del.push(num);
}
int seco(pq& q,pq& del){
    int cnt1=get(q,del);
    if(cnt1==-inf)return -inf;
    q.pop();
    int cnt2=get(q,del);
    q.push(cnt1);
    return cnt2;
}
priority_queue<int>Ans,Ans_del;
priority_queue<int>mxx[N],mx_del[N];
priority_queue<int>se[N],se_del[N];
inline void bfs(int x){
    queue<int>q;q.push(x);
    dis[x][nowdep]=1,tot=0;
    while(!q.empty()){
        int u=q.front();q.pop(),que[tot++]=u;
        for(int v:g[u])
            if(!vis[v]&&dis[u][nowdep]+1<dis[v][nowdep])
                dis[v][nowdep]=dis[u][nowdep]+1,q.push(v);
    }
    return ;
}
void dfs(int x,int ffa){
    siz[x]=1;
    int mx=0;
    for(int v:g[x])
        if(!vis[v]&&v!=ffa){
            dfs(v,x);
            siz[x]+=siz[v];
            mx=max(mx,siz[v]);
        }
    if(max(mx,tot-siz[x])<=tot/2)root=x;
    return ;
}
void work(int x,int ffa,int dep){
    nowdep=dep;
    bfs(x);
    dfs(x,0);
    deep[root]=dep;
    if(ffa)
        for(int i=0;i<tot;i++)mxx[root].push(dis[que[i]][dep]);
    fa[root]=ffa,vis[root]=1;
    int rt=root;
    for(int v:g[root])
        if(!vis[v])
            work(v,rt,dep+1);
    if(ffa)se[ffa].push(get(mxx[rt],mx_del[rt]));
    se[rt].push(0);
    Ans.push(lstans[rt]=get(se[rt],se_del[rt])+seco(se[rt],se_del[rt]));
    return ;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    memset(dis,0x7f,sizeof(dis));
    int n;cin>>n;
    for(int i=1,u,v;i<n;i++)
        cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
    work(1,0,0);
    int q;cin>>q;
    int sum=n;
    while(q--){
        char op;cin>>op;
        if(op=='G'){
            if(sum==1)cout<<"0\n";
            else if(sum==0)cout<<"-1\n";
            else cout<<get(Ans,Ans_del)<<"\n";
        }
        else{
            int x;cin>>x;
            if(flag[x])se[x].push(0),sum++;
            else remove(se[x],se_del[x],0),sum--;
            flag[x]^=1;
            int xx=x;
            while(xx){
                int cnt1=get(se[xx],se_del[xx])+seco(se[xx],se_del[xx]);
                if(cnt1!=lstans[xx])
                remove(Ans,Ans_del,lstans[xx]),Ans.push(lstans[xx]=cnt1);
                if(!fa[xx])break;
                int dep=deep[xx];cnt1=get(mxx[xx],mx_del[xx]);

                if(!flag[x])mxx[xx].push(dis[x][dep]);
                else remove(mxx[xx],mx_del[xx],dis[x][dep]);
                int cnt2=get(mxx[xx],mx_del[xx]);
                if(cnt2!=cnt1)
                    remove(se[fa[xx]],se_del[fa[xx]],cnt1),se[fa[xx]].push(cnt2);
                xx=fa[xx];
            }
        }
    }
    return 0;
}
