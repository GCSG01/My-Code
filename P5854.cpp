#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+5;
int n,a[N],ls[N],rs[N];
int st[N],tot=0;
void insert(int x){
    int lst=0;
    while(tot>0&&a[st[tot]]>a[x])lst=st[tot],tot--;
    ls[x]=lst;
    if(tot)rs[st[tot]]=x;
    st[++tot]=x;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i],insert(i);
    int l=0,r=0;
    for(int i=1;i<=n;i++)
        l^=i*ls[i]+i,r^=i*rs[i]+i;
    cout<<l<<" "<<r;
    return 0;
}