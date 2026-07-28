#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,m;
struct node{
    int u,v,w;
}e[N];
int x[N],y[N],z[N];
int fa[N],siz[N],tmp[N];
int Ans[N];
vector<int>qu[N];int tot;
struct Node{
    int x,y,fx,fy;
}st[N];int top;
int find(int x){return fa[x]==x?x:find(fa[x]);}
void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx==fy)return ;
    if(siz[fx]>siz[fy])swap(fx,fy);
    st[++top]=(Node){x,y,fx,fy};
    siz[fy]+=siz[fx],fa[fx]=fy;
	return ;
}
void rd(int &x){
    char c=getchar();x=0;
    while(c>'9'||c<'0')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    rd(n),rd(m);
    for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1;
    for(int i=1,u,v,w;i<=m;i++)
        rd(x[i]),rd(y[i]),rd(z[i]),e[i]={x[i],y[i],z[i]};
    sort(e+1,e+m+1,[](node A,node B){return A.w<B.w;});
    int q;rd(q);
    for(int i=1;i<=q;i++){
        int k;
        rd(k),Ans[i]=1;
        for(int j=1;j<=k;j++)rd(tmp[j]);
        sort(tmp+1,tmp+k+1,[](int A,int B){return z[A]<z[B];});
        for(int j=1;j<=k;qu[tot].push_back(tmp[j++]))
            if(z[tmp[j]]!=z[tmp[j-1]])qu[++tot].push_back(i);
    }
    sort(qu+1,qu+tot+1,[](vector<int> &A,vector<int> &B){return z[A[1]]<z[B[1]];});
    int now=0;
	for(int i=1;i<=tot;i++){
		int flag=1;
		while(now<=m&&e[now].w<z[qu[i][1]])
            merge(e[now].u,e[now].v),now++;
		for(int j=1;j<qu[i].size();j++){
            int id=qu[i][j];
            if(find(x[id])==find(y[id]))flag=0;
            else merge(x[id],y[id]);
        }
		for(int j=qu[i].size()-1;j>=1;j--){
			int id=qu[i][j];
            while(top>0&&st[top].x==x[id]&&st[top].y==y[id])
                fa[st[top].fx]=st[top].fx,siz[st[top].fy]-=siz[st[top].fx],top--;
		} 
		Ans[qu[i][0]]&=flag;
	}
    for(int i=1;i<=q;i++)
        cout<<(Ans[i]?"YES\n":"NO\n");
    return 0;
}