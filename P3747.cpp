#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e4+5;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
int n,p,m,c;
int a[N];
struct node{
    int v[23];
    int tot=0;
}tr[N<<2];
#define ls p<<1
#define rs p<<1|1
void build(int l,int r,int p){
    if(l==r){
        tr[p].v[++tr[p].tot]=a[l];
        return ;
    }
    
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>p>>m>>c;
    for(int i=1;i<=m;i++)
        cin>>a[i];
    return 0;
}