#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m;
int tr[N<<2];
#define ls(p) (p)<<1
#define rs(p) (p)<<1|1
void update(int l,int r,int p,int s,int t,int val){
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    while(m--){
        int op,l,r;cin>>op>>l>>r;
        if(!op)
            update(1,n,1,l,r,-1);
        else if(op==1){}
    }
    return 0;
}