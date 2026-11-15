#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int ans[N],n;
int tr[N];
vector<int>g;
inline int lowbit(int x){return x&-x;}
inline void update(int x,int val){
    while(x<=n)tr[x]=max(tr[x],val),x+=lowbit(x);
}
inline int query(int x,int s=0){
    while(x)s=max(s,tr[x]),x-=lowbit(x);
    return s;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1,x;i<=n;i++)cin>>x,g.insert(g.begin()+x,i);
    for(int i=0;i<n;i++)
        ans[g[i]]=query(g[i])+1,update(g[i],ans[g[i]]);
    for(int i=1;i<=n;i++)
        cout<<(ans[i]=max(ans[i],ans[i-1]))<<"\n";
}