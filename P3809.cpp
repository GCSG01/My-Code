#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int N=1e6+5;
ull bas[N],hs[N];
int id[N];
char a[N];
int n;
ull get(int x,int y){
    return hs[y]-hs[x-1]*bas[y-x+1];
}
bool cmp(int A,int B){
    int l=0,r=min(n-A+1,n-B+1)+1;
    while(l+1<r){
        int mid=(l+r)/2;
        if(get(A,A+mid-1)!=get(B,B+mid-1))r=mid;
        else l=mid;
    }
    if(A+l>n||B+l>n)return A>B;
    else return a[A+l]<a[B+l];
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    string TEMP;cin>>TEMP,n=TEMP.size();
    for(int i=1;i<=n;i++)a[i]=TEMP[i-1];
    bas[0]=1;
    for(int i=1;i<=n;i++)
        bas[i]=bas[i-1]*4587,hs[i]=hs[i-1]*4587+a[i],id[i]=i;
    stable_sort(id+1,id+n+1,cmp);
    for(int i=1;i<=n;i++)
        cout<<id[i]<<" ";
    return 0;
}