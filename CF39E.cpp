#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
unordered_map<int,int>f[35];
// map<int,int>f[35];
int dfs(int a,int b,int n){
    if(f[b].count(a))return f[b][a];
    if(pow(a,b)>=n)return f[b][a]=1;
    if(b>30)return 0;
    int x=dfs(a+1,b,n);
    if(x==-1)return f[b][a]=1;
    int y=dfs(a,b+1,n);
    if(y==-1)return f[b][a]=1;
    if(!x||!y)return f[b][a]=0;
    return f[b][a]=-1;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int a,b,n;cin>>a>>b>>n;
    int ans=dfs(a,b,n);
    if(ans==1)cout<<"Masha";
    else if(ans==-1)cout<<"Stas";
    else cout<<"Missing";
    return 0;
}