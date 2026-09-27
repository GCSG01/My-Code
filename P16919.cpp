#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=6e5+5;
int n,a[N];
int ans[N],t[N];
bool flag[N];
multiset<int>st;
vector<int>v[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        for(int i=1;i<=n;i++)
            t[i]=ans[i]=flag[i]=0,v[i].clear();
        st.clear();
        cin>>n;
        for(int i=1;i<=2*n;i++)
            cin>>a[i];
        for(int i=1;i<=2*n;i++)
            t[a[i]]++;
        for(int i=1;i<=2*n;i++)
            if(t[a[i]]==1)
                st.insert(a[i]);
        for(int i=1;i<=n;i++){
            if(t[i]<=1)continue;
            t[i]-=2;
            while(t[i])
                if(!st.empty()&&*st.begin()<=i)
                    v[i].push_back(*st.begin()),st.erase(st.begin()),t[i]--;
                else st.insert(i),t[i]--;
            flag[i]=1;
        }
        int tot=0;
        for(int i=1;i<=n;i++){
            if(!flag[i])continue;
            ans[++tot]=i;
            for(int j:v[i])
                ans[++tot]=j;
        }
        if(tot!=n)
            cout<<"No\n";
        else{
            cout<<"Yes\n";
            for(int i=1;i<=tot;i++)
                cout<<ans[i]<<" ";
            cout<<"\n";
        }
    }
    return 0;
}