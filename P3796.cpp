#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,tot,ans;
int vis[N];
string s[N];
string t;
struct node{
    int son[26],flag,fail;
    void clear(){
        memset(son,0,sizeof son);
        flag=fail=0;
    }
}tr[N];
queue<int>q;
void insert(string s,int sum){
    int x=1;
    for(int i=0;i<s.size();i++){
        int c=s[i]-'a';
        if(!tr[x].son[c])tr[x].son[c]=++tot;
        x=tr[x].son[c];
    }
    tr[x].flag=sum;
    return ;
}
void init(){
    for(int i=1;i<=tot;i++)tr[i].clear();
    for(int i=1;i<=n;i++)vis[i]=0;
    tot=1,ans=0;
    return ;
}
void getfail(){
    for(int i=0;i<26;i++)tr[0].son[i]=1;
    q.push(1),tr[1].fail=0;
    while(!q.empty()){
        int x=q.front();q.pop();
        int fl=tr[x].fail;
        for(int i=0;i<26;i++){
            int y=tr[x].son[i];
            if(!y){
                tr[x].son[i]=tr[fl].son[i];
                continue;
            }
            tr[y].fail=tr[fl].son[i],q.push(y);
        }
    }
    return ;
}
void query(string t){
    int x=1;
    for(int i=0;i<t.size();i++){
        int v=t[i]-'a',k=tr[x].son[v];
        while(k>1){
            if(tr[k].flag)vis[tr[k].flag]++;
            k=tr[k].fail;
        }
        x=tr[x].son[v];
    }
    return ;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    while(cin>>n){
        if(!n)break;
        init();
        for(int i=1;i<=n;i++)cin>>s[i],insert(s[i],i);
        cin>>t;
        getfail();
        query(t);
        int ans=0;
        for(int i=1;i<=n;i++)ans=max(ans,vis[i]);
        cout<<ans<<"\n";
        for(int i=1;i<=n;i++)
            if(vis[i]==ans)
                cout<<s[i]<<"\n";
    }
    return 0;
}