#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,m,a[N];
vector<int>g[N];
int fa[N];
int tag[N];
int tot=0,bas[N*25],ch[N*25][2],sum[N*25],siz[N*25];
void dfs(int x){
    for(auto y:g[x])
		if(y!=fa[x])
            fa[y]=x,dfs(y);
}
int nw(int x){
	return bas[++tot]=x,sum[tot]=siz[tot]=ch[tot][0]=ch[tot][1]=0,tot;
}
void push_up(int x){
	siz[x]=sum[x]=0;
	if(ch[x][0])
		siz[x]+=siz[ch[x][0]],sum[x]^=sum[ch[x][0]];
	if(ch[x][1]){
		siz[x]+=siz[ch[x][1]],sum[x]^=sum[ch[x][1]];
		if(siz[ch[x][1]]&1)sum[x]|=1<<bas[x];
	}
}
void insert(int u,int x){
	if(bas[u]>20)
        return siz[u]++,void();
	else if(x>>bas[u]&1){
        if(!ch[u][1])
            ch[u][1]=nw(bas[u]+1);
        insert(ch[u][1],x);
    }
    else{
        if(!ch[u][0])
            ch[u][0]=nw(bas[u]+1);
        insert(ch[u][0],x);
    }
	return push_up(u);
}
void erase(int u,int x){
	if(bas[u]>20)
        return siz[u]--,void();
    if(x>>bas[u]&1)
        erase(ch[u][1],x);
    else erase(ch[u][0],x);
    return push_up(u);
}
void update(int u){
	swap(ch[u][0],ch[u][1]);
	if(ch[u][0])
        update(ch[u][0]);
	return push_up(u);
}
int rt[N];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1,u,v;i<n;i++)
        cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	dfs(1);
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)rt[i]=nw(0);
	for(int i=2;i<=n;i++)insert(rt[fa[i]],a[i]);
	while(m--){
		int op,x,v;cin>>op;
		if(op==1){
			cin>>x;
			tag[x]++;
			update(rt[x]);
			if(x>1){
				if(fa[x]>1)erase(rt[fa[fa[x]]],a[fa[x]]+tag[fa[fa[x]]]);
				a[fa[x]]++;
				if(fa[x]>1)insert(rt[fa[fa[x]]],a[fa[x]]+tag[fa[fa[x]]]);
			}
		}
		else if(op==2){
            cin>>x>>v;
			if(x>1)erase(rt[fa[x]],a[x]+tag[fa[x]]);
			a[x]-=v;
			if(x>1)insert(rt[fa[x]],a[x]+tag[fa[x]]);
		}
		else{
			cin>>x;
			if(x>1){
				if(fa[x]>1)
                    cout<<(sum[rt[x]]^(a[fa[x]]+tag[fa[fa[x]]]))<<"\n";
				else cout<<(sum[rt[x]]^a[fa[x]])<<"\n";
			}
			else cout<<sum[rt[x]]<<"\n";
		}
	}
	return 0;
}