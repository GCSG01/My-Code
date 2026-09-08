#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
typedef unsigned int ui ;
ui randNum( ui& seed , ui last , const ui m){ 
    seed = seed * 17 + last ; return seed % m + 1; 
}
#define int long long
const int N=2e6+5;
ui n,m,lst,seed;
int a[N];
void print(int x){
    if(x<=9)return cout<<x,void();
    print(x/10),cout<<x%10;
}
tree<pair<int,int>,null_type,greater<pair<int,int>>,rb_tree_tag,tree_order_statistics_node_update>tr;
signed main(){
    int T;cin>>T,lst=7;
    while(T--){
        cin>>m>>n>>seed,tr.clear();
        for(int i=1;i<=m;i++)tr.insert({a[i]=1500000-1,i});
        for(int i=1,x,y;i<=n;i++){
            x=randNum(seed,lst,m),y=randNum(seed,lst,m);
            auto pos=tr.find({a[x],x});
            tr.erase(pos),a[x]+=1500000-y;
            tr.insert({a[x],x});
            print(lst=tr.order_of_key({a[x],m+1})),puts("");
        }
    }
}