#include<bits/stdc++.h>
// #define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
const int N=65;
int n;
int pre[N][N];
int dp[N][N][N][N];
int get(int x1,int y1,int x2,int y2){
    return pre[x2][y2]-pre[x1-1][y2]-pre[x2][y1-1]+pre[x1-1][y1-1];
}
int solve(int x1,int y1,int x2,int y2){
    if(x2<x1||y2<y1)return 0;
    if(get(x1,y1,x2,y2)<=2)return get(x1,y1,x2,y2);
    if(dp[x1][y1][x2][y2]!=-1)return dp[x1][y1][x2][y2];
    int ans=max(x2-x1+1,y2-y1+1);
    if(x2-x1>y2-y1)
        for(int i=x1;i<x2;i++)
            ans=min(ans,solve(x1,y1,i,y2)+solve(i+1,y1,x2,y2));
    else for(int i=y1;i<y2;i++)
        ans=min(ans,solve(x1,y1,x2,i)+solve(x1,i+1,x2,y2));
    return dp[x1][y1][x2][y2]=ans;
}
signed main(){
    freopen("detection.in","r",stdin);
    freopen("detection.out","w",stdout);
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            char c;cin>>c;
            pre[i][j]=pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1]+(c=='T');
        }
    memset(dp,-1,sizeof(dp));
    cout<<solve(1,1,n,n)<<"\n";
    return 0;
}