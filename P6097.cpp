#include<bits/stdc++.h>
using namespace std;
const int N=1<<20+5;
int n;
int a[N],b[N];
void XOR(int *a){

}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)cin>>b[i];
    XOR(a),XOR(b);
    for(int i=1;i<=n;i++){}
    return 0;
}