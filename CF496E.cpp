#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
struct node{
	int r,k,id;
	bool operator<(const node&x)const{return r<x.r;}
};
struct node2{
    int l,r,k,id;
}a[N],b[N],c[N];
int n,m,ans[100005];
multiset<node>s;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
        cin>>a[i].l>>a[i].r,a[i].id=i,c[i]=a[i];
	cin>>m;
	for(int i=1;i<=m;i++)
        cin>>b[i].l>>b[i].r>>b[i].k,b[i].id=i,c[i+n]=b[i];
	sort(c+1,c+n+m+1,[](node2 x,node2 y){
        return x.l!=y.l?x.l<y.l:x.k>y.k;
    });
	for(int i=1;i<=n+m;i++){
		if(c[i].k){
			node tmp;
            tmp.r=c[i].r,tmp.id=c[i].id,tmp.k=c[i].k;
			s.insert(tmp);
		}
        else{
			auto it=s.lower_bound((node){c[i].r,0,0});
			if(it==s.end())
				return cout<<"NO\n",0;
			ans[c[i].id]=(*it).id;
			node tmp=*it;
			s.erase(it);
			tmp.k--;
			if(tmp.k)s.insert(tmp);
		}
	}
	cout<<"YES\n";
	for(int i=1;i<=n;i++)
        cout<<ans[i]<<" ";
	return 0;
}