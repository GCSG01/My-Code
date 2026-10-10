#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
mt19937 rd(time(0));

int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    freopen("a.in","w",stdout);
    int n=1e7;
    cout<<n<<"\n";
    for(int i=1;i<=n;i++)
        cout<<rd()<<" ";
}