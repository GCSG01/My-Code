#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
int p,b,n;
map<int,int>f;
int power(int x,int y){
    int s=1;
    while(y){
        if(y&1)s*=x,s%=p;
        x*=x,x%=p,y>>=1;
    }
    return s;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>p>>b>>n;
    int B=ceil(sqrt(p));
    for(int i=1;i<=B;i++)
        f[n*power(b,i)%p]=i;
    int cnt=1;
    for(int i=1;i<=B;i++){
        cnt=cnt*power(b,B)%p;
        if(f.count(cnt)){
            return cout<<(B*i%p-f[cnt]+p)%p,0;
        }
    }
    cout<<"no solution";
    return 0;
}