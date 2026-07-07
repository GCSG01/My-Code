#include<bits/stdc++.h>
using namespace std;
const int N=2e3+5;
int n;
bitset<N>f[N];
void guass(){
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++)
            if(f[j][i]){
                swap(f[i],f[j]);
                break;
            }
        for(int j=1;j<=n;j++)
            if(i!=j&&f[j][i]==1)
                f[j]^=f[i];
    }
    return ;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1,m;i<=n;i++){
        cin>>m;
        if(m&1||!m)f[i][i]=f[i][n+1]=1;
        for(int j=1,x;j<=m;j++)
            cin>>x,f[i][x]=1;
    }
    guass();
    int ans=0;
    for(int i=1;i<=n;i++)if(f[i][n+1])ans++;
    cout<<ans<<"\n";
    for(int i=1;i<=n;i++)if(f[i][n+1])cout<<i<<" ";
    return 0;
}