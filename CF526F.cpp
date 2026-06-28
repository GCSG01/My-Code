#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
int n;
int a[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1,x,y;i<=n;i++)
        cin>>x>>y,a[x]=y;
    
    return 0;
}