#include<bits/stdc++.h>
using namespace std;
const int N=105,p=2017;
vector<int>e[N];
struct node{
    int n;
    int a[N][N];
    node(){
        memset(a,0,sizeof a);
    }
    void init(){
        for(int i=1;i<=n;i++)
            a[i][i]=1;
        return ;
    }
    node operator*(const node &B)const{
        node c;c.n=n;
        for(int i=1;i<=n;i++)
            for(int k=1;k<=n;k++)
                for(int j=1;j<=n;j++)
                    c.a[i][j]+=a[i][k]*B.a[k][j]%p,c.a[i][j]%=p;
        return c;
    }
};
node power(node A,int k){
    node ans;ans.n=A.n,ans.init();
    while(k){
        if(k&1)ans=ans*A;
        A=A*A,k>>=1;
    }
    return ans;
}
void print(node A){
    for(int i=1;i<=A.n;i++,cout<<"\n")
        for(int j=1;j<=A.n;j++)
            cout<<A.a[i][j]<<" ";
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n,m;cin>>n>>m;
    for(int i=1,u,v;i<=m;i++)
        cin>>u>>v,e[u].push_back(v),
        e[v].push_back(u);
    node A;A.n=n+1;
    A.a[1][1]=1;
    for(int i=1;i<=n;i++){
        A.a[i+1][1]=A.a[i+1][i+1]=1;
        for(auto j:e[i])
            A.a[i+1][j+1]=1;
    }
    int t;cin>>t;
    A=power(A,t);
    // print(A);
    int ans=0;
    for(int i=1;i<=n+1;i++)ans+=A.a[2][i],ans%=p;
    cout<<ans;
    return 0;
}