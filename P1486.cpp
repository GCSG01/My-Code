#include<bits/stdc++.h>
#include<bits/extc++.h>
#define int long long
using namespace std;
using namespace __gnu_pbds;
struct node{
    int v,id;
    bool operator>(node b)const{
        return v==b.v?id>b.id:v>b.v;
    }
};
tree<node,null_type,greater<node>,rb_tree_tag,tree_order_statistics_node_update>tr,tr2;
signed main(){  
    ios::sync_with_stdio(0);cin.tie(0);
    int n,m;cin>>n>>m;
    int ans=0,sum=0;
    while(n--){
        char op;int k;cin>>op>>k;
        if(op=='I'){
            k+=sum;
            if(k>=m)tr.insert({k,n});
        }
        else if(op=='A')m-=k,sum-=k;
        else if(op=='S')
            m+=k,sum+=k,tr.split({m,-1},tr2),ans+=tr2.size();
        else if(k>tr.size())cout<<"-1\n";
        else cout<<tr.find_by_order(k-1)->v-sum<<"\n";
    }
    cout<<ans;
}