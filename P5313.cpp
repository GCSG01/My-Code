#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,B=64;
int n,m,a[N];
struct node{
    int l,r,b,id;
}qu[N];
inline void rd(int &x){
    char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    x=c-'0';c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
}