#include<bits/stdc++.h>
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    int f=1;
    while(c<'0'||c>'9'){
        if(c=='-'){f=-1;break;}
        c=getchar();
    }
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')
        x=x*10+c-'0',c=getchar();
    x=x*f;
}
const int N=3e5+5;
int n,k;
int a[N],b[N];
int ans[N];
struct ndq{
    int x,y,id;
}qu[N];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)cin>>b[i];
    cin>>k;
    for(int i=1;i<=k;i++)cin>>qu[i].x>>qu[i].y,qu[i].id=i;
    return 0;
}