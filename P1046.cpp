#include<bits/stdc++.h>
using namespace std;
const int N=15;
int a[N];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
	for(int i=1;i<=10;i++)
        cin>>a[i];
	int x;cin>>x;
    int s=0;
	for(int i=1;i<=10;i++)
		if(x+30>=a[i])s++;
	cout<<s;
	return 0;
}