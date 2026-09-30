#include<bits/stdc++.h>
#include<bits/extc++.h>
#define int long long
using namespace std;
using namespace __gnu_pbds;
const int N=5e5+5;
int n,m,tik[N],root[N];
random_device rnd;
mt19937 rd(rnd());
tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>tr[N];
int get(int x,int l,int r){
	return tr[x].order_of_key(r+1)-tr[x].order_of_key(l);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>tik[i],tr[tik[i]].insert(i);
    while(m--){
        int l,r,s,k;cin>>l>>r>>s>>k;
        int len=r-l+1,ans=s;
        for(int i=1;i<=20;i++){
            int x=rd()%len+l;
            x=tik[x];
            if(get(x,l,r)>(len>>1)){
                ans=x;break;
            }
        }
        for(int i=1,x;i<=k;i++){
            cin>>x;
            tr[tik[x]].erase(x);
			tr[ans].insert(x);
			tik[x]=ans;
        }
        cout<<ans<<"\n";
    }
    int ans=-1;
    for(int i=1;i<=20;i++){
        int x=rand()%n+1;
        x=tik[x];
        if(get(x,1,n)>(n>>1)){
            ans=x;break;
        }
    }
    cout<<ans;
}