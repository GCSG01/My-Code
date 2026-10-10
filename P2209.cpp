#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,g,b,d;
int st[N];
struct node{
    int x,y,p;
}a[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>g>>b>>d;
    for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y;
    sort(a+1,a+n+1,[](node A,node B){return A.x<B.x;}),a[++n]={d,0,0};
    int top=0;
    for(int i=1;i<=n;i++){
        while(top&&a[st[top]].y>=a[i].y)
            a[st[top--]].p=i;
        st[++top]=i;
    }
    // for(int i=1;i<=n;i++)
    //     cout<<a[i].x<<" "<<a[i].y<<" "<<a[i].p<<"\n";
    int ans=0;b-=a[1].x;
    for(int i=1;i<n;){
        if(b<0)return cout<<-1,0;
        int j=a[i].p;
        if(a[j].x-a[i].x<=g){
            int cnt=max(0ll,a[j].x-a[i].x-b);
            ans+=cnt*a[i].y,b+=cnt-a[j].x+a[i].x,i=j;
        }
        else ans+=(g-b)*a[i].y,b=g-a[i+1].x+a[i].x,i++;
        // cout<<i<<" "<<ans<<" "<<g<<" "<<b<<"\n";
    }
    cout<<ans;
}