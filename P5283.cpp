#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+5;
int n,k;
int s[N];
int trie[N][2],siz[N],idx;
struct node{
    int id,rk,v;
    bool operator <(const node &B)const{
        return v<B.v;
    }
};
priority_queue<node>q;
void ins(int x){
    int now=0;
    for(int i=31;i>=0;i--){
        int ch=(x>>i)&1;siz[now]++;
        if(!trie[now][ch])trie[now][ch]=++idx;
        now=trie[now][ch];
    }
    siz[now]++;
    return ;
}
int query(int x,int k){
    int now=0,ans=0;
    for(int i=31;i>=0;i--){
        int ch=(x>>i)&1;
        if(!trie[now][ch^1])now=trie[now][ch];
        else if(k<=siz[trie[now][ch^1]])now=trie[now][ch^1],ans+=(1ll<<i);
        else k-=siz[trie[now][ch^1]],now=trie[now][ch];
    }
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>k;
    ins(0);
    for(int i=1,x;i<=n;i++)cin>>x,s[i]=s[i-1]^x,ins(s[i]);
    int ans=0;
    for(int i=0;i<=n;i++)
        q.push({i,1,query(s[i],1)});
    for(int i=1;i<=k*2;i++){
        node now=q.top();q.pop();
        ans+=now.v;
        if(now.rk<n)q.push({now.id,now.rk+1,query(s[now.id],now.rk+1)});
    }
    cout<<ans/2;
    return 0;
}