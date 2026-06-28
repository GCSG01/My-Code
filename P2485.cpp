#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
int power(int a,int b,int p){
    int s=1;
    while(b){
        if(b&1)s=s*a,s%=p;
        a=a*a,a%=p,b>>=1;
    }
    return s;
}
int bsgs(int a,int p,int b){
    if(b==1)return 0;
    if(a%p==b%p)return 1;
    if(a%p==0)return -1;
    a%=p,b%=p;
    int A=1,B=sqrt(p)+1;
    map<int,int>f;
    for(int i=1;i<=B;i++)
        A=A*a%p,f[A*b%p]=i;
    for(int i=1,cnt=A;i<=B;i++){
        if(f.count(cnt))
            return i*B-f[cnt];
        cnt=cnt*A%p;
    }
    return -1;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T,K;cin>>T>>K;
    while(T--){
        int y,z,p;cin>>y>>z>>p;
        if(K==1)cout<<power(y,z,p)<<"\n";
        else if(K==2){
            if(y%p==0)cout<<"Orz, I cannot find x!\n";
            else cout<<(z*power(y,p-2,p)%p)<<"\n";
        }
        else{
            int ans=bsgs(y,p,z);
            if(ans==-1)cout<<"Orz, I cannot find x!\n";
            else cout<<ans<<"\n";
        }
    }
    return 0;
}