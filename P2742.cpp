#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n;
struct node{
    double x,y;
}a[N];
int st[N],top;
double dis(int x,int y){
    return sqrt((a[x].y-a[y].y)*(a[x].y-a[y].y)+(a[x].x-a[y].x)*(a[x].x-a[y].x));
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y;
    sort(a+1,a+n+1,[](node A,node B){return A.x==B.x?A.y<B.y:A.x<B.x;});
    double ans=0;
    st[top=1]=1;
    for(int i=2;i<=n;st[++top]=i++)
        while(top>1&&(a[i].y-a[st[top-1]].y)*(a[i].x-a[st[top]].x)>=(a[i].y-a[st[top]].y)*(a[i].x-a[st[top-1]].x))top--;
    for(int i=1;i<top;i++)ans+=dis(st[i],st[i+1]);
    st[top=1]=1;
    for(int i=2;i<=n;st[++top]=i++)
        while(top>1&&(a[i].y-a[st[top-1]].y)*(a[i].x-a[st[top]].x)<=(a[i].y-a[st[top]].y)*(a[i].x-a[st[top-1]].x))top--;
    for(int i=1;i<top;i++)ans+=dis(st[i],st[i+1]);
    cout<<fixed<<setprecision(2)<<ans;
    return 0;
}