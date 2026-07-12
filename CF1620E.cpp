#include<bits/stdc++.h>
using namespace std;
const int N=6e5+5;
int a[N],tot=0;
int fa[N];
int t[N];
int q;
struct node{
    int op,x,y;
}qu[N];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>q;
    for(int i=1;i<=N-5;i++)fa[i]=i;
    for(int i=1;i<=q;i++)
        cin>>qu[i].op>>qu[i].x,qu[i].op==2?cin>>qu[i].y,0:0;
    for(int i=q;i>=1;i--)
        if(qu[i].op==1)
            a[++tot]=fa[qu[i].x];
        else fa[qu[i].x]=fa[qu[i].y];
    for(int i=tot;i>=1;i--)cout<<a[i]<<" ";
    return 0;
}