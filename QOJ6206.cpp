#include "cards.h"
#include <bits/stdc++.h>
using namespace std;
int K,sum;
vector<vector<int>>a;
void init(int k) {
    K=k,sum=1;
    for(int i=1;i<=K-2;i++)sum*=i;
    sum=sum*2+1;
    vector<int>c(K-2);
    iota(c.begin(),c.end(),0);
    do{
        a.push_back(c);
    }while(next_permutation(c.begin(),c.end()));
}
void init_assistant(int N,int k){init(k);}
void init_magician(int N,int k){init(k);}
vector<int> choose_cards(vector<int> cards){
    vector<int>b[K-1];
    for(int &x:cards)
        x--,b[x/sum].push_back(x%sum);
    int cnt=-1,p=-1,d=-1;
    for(int i=0;i<K-1;i++){
        if(b[i].size()<2)continue;
        b[i].push_back(b[i][0]);
        for (int j=1;j<static_cast<int>(b[i].size());j++){
            d=(b[i][j]-b[i][j-1]+sum)%sum;
            if(d<=sum/2){
                cnt=b[i][j]+sum*i;
                p=b[i][j-1]+sum*i;
                break;
            }
        }
        if(cnt!=-1)break;
    }
    vector<int>c;
    for(int x:cards)
        if(x!=cnt&&x!=p)
            c.push_back(x);
    vector<int>pr;pr.push_back(p+1);
    for (int i=0;i<K-2;i++)
        pr.push_back(c[a[d-1][i]]+1);
    return pr;
}
int find_discarded_card(vector<int> cards){
    vector<int>b(cards.begin()+1,cards.end());
    sort(b.begin(), b.end());
    vector<int>c;
    for(int i=1; i<static_cast<int>(cards.size());i++)
        c.push_back(lower_bound(b.begin(),b.end(),cards[i])-b.begin());
    int ans=(cards[0]-1+lower_bound(a.begin(),a.end(),c)-a.begin()+1)%sum;
    return ans+(cards[0]-1)/sum*sum+1;
}