#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,d,m;
struct node{
    int x,v;
}a[N];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>d>>n>>m;
    for(int i=1;i<=m;i++)cin>>a[i].x>>a[i].v;
    sort(a+1,a+m+1,[](node A,node B){
        return A.x<B.x;
    });
    return 0;
}