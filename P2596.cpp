#include<bits/stdc++.h>
using namespace std;
const int N=8e4+5;
int n,m,a[N],pos[N];
namespace FHQ_Treap{
    mt19937 rnd(time(0));
    int ls[N],rs[N],pri[N],v[N],siz[N],tag[N],fa[N];
    int tot,root;
    inline int add_new(int p){
        return pri[++tot]=rnd()%10000000,v[tot]=p,pos[p]=tot,siz[tot]=1,tot;
    }
    inline void push_up(int p){
        siz[p]=siz[ls[p]]+siz[rs[p]]+1;
        if(ls[p])fa[ls[p]]=p;
		if(rs[p])fa[rs[p]]=p;
    }
    void push_down(int p){
        if(!tag[p])return ;
        swap(ls[p],rs[p]),tag[ls[p]]^=1,tag[rs[p]]^=1,tag[p]=0;
    }
    int merge(int x,int y){
        if(!x||!y){
            if(x+y)fa[x+y]=0;
            return x+y;
        }
        push_down(x),push_down(y);
        if(pri[x]<pri[y])
            return rs[x]=merge(rs[x],y),push_up(x),fa[x]=0,x;
        else return ls[y]=merge(x,ls[y]),push_up(y),fa[y]=0,y;
    }
    void split(int p,int &x,int &y,int k){
        if(!p)return x=y=0,void();
        push_down(p);
        if(k>=siz[ls[p]]+1)
            x=p,split(rs[p],rs[x],y,k-siz[ls[p]]-1),push_up(p),fa[x]=0;
        else y=p,split(ls[p],x,ls[y],k),push_up(p),fa[x]=0;
    }
    void build(){
    root=0;
    for(int i=1;i<=n;i++)
        root=merge(root,add_new(a[i]));
	}
    int getrank(int p){
		int res=siz[ls[p]]+1;
		while(fa[p]){
			int f=fa[p];
			if(rs[f]==p)
                res+=siz[ls[f]]+1;
			p=f;
		}
		return res;
	}
	int kth(int p,int k){
		while(p){
			if(k<=siz[ls[p]])
				p=ls[p];
			else if(k==siz[ls[p]]+1)
				return v[p];
			else k-=siz[ls[p]]+1,p=rs[p];
		}
		return 0;
	}
	void move_to(int p,int k,int rx=0){
		if(!rx)rx=getrank(p);
		if(k<1)k=1;
		if(k>n)k=n;
		if(rx==k)return;
		int a,b,c,d;
		split(root,a,b,rx-1);
		split(b,c,d,1);
		ls[c]=rs[c]=fa[c]=0,siz[c]=1;
		root=merge(a,d);
		split(root,a,b,k-1);
		root=merge(merge(a,c),b);
	}
}
using namespace FHQ_Treap;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    build();
    while(m--){
        string op;
        int s,t;cin>>op>>s;
        if(op=="Top")move_to(pos[s],1);
        else if(op=="Bottom")move_to(pos[s],n);
        else if(op=="Insert"){
            int cnt=getrank(pos[s]);
            cin>>t,move_to(pos[s],cnt+t,cnt);
        }
        else if(op=="Ask")cout<<getrank(pos[s])-1<<"\n";
        else cout<<kth(root,s)<<"\n";
    }
    return 0;
}