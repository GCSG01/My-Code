#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;

int T;
char s[N],t[N];

signed main(){
	scanf("%d",&T);
	while(T--){
		unordered_map<string,bool> m;
		int q;
		scanf("%s%d",s,&q);
		int s1=strlen(s);
		while(q--){
			scanf("%s",t);
			string b=t;
			if(m.count(b)){
				if(m[b]) printf("Yes\n");
				else printf("No\n");
				continue;
			}
			int t1=strlen(t);
			int f2=s1/t1;
			int f1=f2*t1;
			int i,j,k,o;
			for(i=0,j=0,k=0,o=0;i<s1 && k<f2;i++){
				if(i-o>s1-f1) break;//优化循环次数 
				if(s[i]==t[j]){
					j++;
					o++;
					if(j==t1) j=0,k++;
				}
			}
			if(k>=f2) printf("Yes\n");
			else printf("No\n");
			m[t]=(k>=f2);
		}
	}

	return 0;
}