#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,q,c[N],Ans[N];
int bit[N],pos[N];
struct node{
    int l,r,id;
}qu[N];
void insert(int x,int p){
    for(int i=30;i>=0;i--)
        if(x&(1<<i)){
            if(!bit[i])
				return bit[i]=x,pos[i]=p,void();
			if(pos[i]<p)
                swap(pos[i],p),swap(x,bit[i]);
			x^=bit[i];
        }
}
int query(int p){
	int ans=0;
	for(int i=20;i>=0;i--)
		if(pos[i]>=p&&ans<(ans^bit[i]))
			ans^=bit[i];
	return ans;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>c[i];
    cin>>q;
    for(int i=1;i<=q;i++)
        cin>>qu[i].l>>qu[i].r,qu[i].id=i;
    sort(qu+1,qu+q+1,[](node A,node B){return A.r<B.r;});
    int r=0;
    for(int i=1;i<=n;i++){
        int l=r+1;insert(c[i],i);
        while(qu[r+1].r<=i&&r<q)
            r++,Ans[qu[r].id]=query(qu[r].l);
    }
    for(int i=1;i<=q;i++)
        cout<<Ans[i]<<"\n";
}