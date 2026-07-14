#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int v[N];
int n,q;
void Update(int x,int y,int z){

}
int Query(int x,int y){
    int ans=0;
    return ans;
}
void dfs1(int )
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>v[i];
    while(q--){
        string op;int x,y,z;cin>>op>>x>>y;
        if(op[0]=='U')
            cin>>z,Update(x,y,z);
        else{
            if(y-x+1>30)cout<<"NO\n";
            cout<<Query(x,y)<<"\n";
        }
    }
    return 0;
}