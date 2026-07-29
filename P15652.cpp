#include<bits/stdc++.h>
using namespace std;
void init(int, int);
vector<int> perm(int);
int query(int, int);
void init(int C,int T){
	return ;
}
const int N=3e5+5;
int a[N];
int suf[N];
int pre[N];
bool vis[N];
struct node{
    int i,v;
}b[N];
vector<int> perm(int n){
    memset(a,-1,sizeof a);
    memset(pre,-1,sizeof pre);
    memset(suf,-1,sizeof suf);
    memset(vis,0,sizeof vis);
    int pos=n-1;
    for(;pos>=1;pos--){
        suf[pos]=query(0,pos-1);
        if(suf[pos]==0)break;
    }
    if(!pos)pos=1;
    int tot=0;
    a[n-1]=suf[n-1],vis[a[n-1]]=1;
    for(int i=n-2;i>=pos;i--)
        if(suf[i]!=suf[i+1])a[i]=suf[i],vis[a[i]]=1;
        else b[++tot]={i,suf[i]};
    for(int i=0;i<pos;i++)
        pre[i]=query(i+1,n-1);
    a[0]=pre[0],vis[a[0]]=1;
    for(int i=1;i<pos;i++)
        if(pre[i]!=pre[i-1])
            a[i]=pre[i],vis[a[i]]=1;
        else b[++tot]={i,pre[i]};
    sort(b+1,b+tot+1,[](node A,node B){
        return A.v<B.v;
    });
    for(int i=n-1;i;i--)
        if(!vis[i])a[b[tot].i]=i,tot--;
    vector<int>ans;
    for(int i=0;i<n;i++)ans.push_back(a[i]);
    return ans;
}