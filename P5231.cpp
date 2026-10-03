#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5,M=2e2;
int n,m,tot;
string s,t[N];
int trie[N][4],flag[N];
inline int get(char c){
    if(c=='E')return 0;
    if(c=='S')return 1;
    if(c=='W')return 2;
    return 3;
}
void insert(string t){
    int now=0;
    for(int i=0;i<t.size();i++){
        int c=get(t[i]);
        if(!trie[now][c])trie[now][c]=++tot;
        now=trie[now][c];
    }
}
void upd(int x){
    int now=0;
    while(x<=n){
        int c=get(s[x]);
        now=trie[now][c];
        if(!now)return ;
        flag[now]=1,x++;
    }
}
int query(string t){
    int now=0;
    for(int i=0;i<t.size();i++){
        int c=get(t[i]);
        now=trie[now][c];
        if(!flag[now])return i;
    }
    return t.size();
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>s,s=" "+s;
    for(int i=1;i<=m;i++)
        cin>>t[i],insert(t[i]);
    for(int i=1;i<=n;i++)upd(i);
    for(int i=1;i<=m;i++)
        cout<<query(t[i])<<"\n";
}