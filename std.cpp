#include <iostream>
#include <cstdio>
#include <algorithm>
#define N 200001

using namespace std;

int n,m,M,M2,a[N],ls[N * 2],siz,ans[N * 2],op2[N * 2];
int t[N * 2];

struct Q
{
    int op,l,r,k,x,y,id;
}q[N * 2],q1[N * 2],q2[N * 2];

int lowbit( int x )
{
    return x & ( -x );
}

void upd( int x , int y )
{
    for( int i = x ; i <= siz ; i += lowbit( i ) )
        t[i] += y;
    return;
}

int que( int x )
{
    int sum = 0;
    for( int i = x ; i >= 1 ; i-= lowbit( i ) )
        sum += t[i];
    return sum;
}

void solve( int l , int r , int ql , int qr )
{
    if( ql > qr ) return;
    if( l == r )
    {
        for( int i = ql ; i <= qr ; i ++ )
            if( q[i].op == 2 )
                ans[q[i].id] = l;
        return;        
    }
    int mid = ( l + r ) / 2,L = 0,R = 0;
    for( int i = ql ; i <= qr ; i ++ )
    {
        if( q[i].op == 0 )
        {
            if( q[i].y <= mid )
            {
                L ++;
                q1[L] = q[i];
                upd( q[i].x , 1 );
            }
            else
            {
                R ++;
                q2[R] = q[i];
            }
        }
        if( q[i].op == 1 )
        {
            if( q[i].y <= mid )
            {
                L ++;
                q1[L] = q[i];
                upd( q[i].x , -1 );
            }
            else
            {
                R ++;
                q2[R] = q[i];
            }
        }
        if( q[i].op == 2 )
        {
            int nw = que( q[i].r ) - que( q[i].l - 1 );
            if( nw >= q[i].k ) L ++,q1[L] = q[i];
            else R ++,q2[R] = q[i],q2[R].k -= nw;
        }
    }
    
    for( int i = ql ; i <= qr ; i ++ )
    {
        if( q[i].op == 0 && q[i].y <= mid ) upd( q[i].x , -1 );
        if( q[i].op == 1 && q[i].y <= mid ) upd( q[i].x , 1 );
    }
    int i = ql;
    for( int j = 1 ; j <= L ; i ++ , j ++ )
        q[i] = q1[j];
    for( int j = 1 ; j <= R ; i ++ , j ++ )
        q[i] = q2[j];
    solve( l , mid , ql , ql + L - 1 );
    solve( mid + 1 , r , ql + L , qr );
    return;
}

int main()
{
    ios::sync_with_stdio( false );
    cin.tie( 0 );
    cout.tie( 0 );
    cin >> n >> m;
    for( int i = 1 ; i <= n ; i ++ )
    {
        cin >> a[i];
        ls[++ siz] = a[i];
        M ++;
        q[M].id = M;
        q[M].op = 0;
        q[M].x = i;
        q[M].y = a[i];
    }
    int l,r,k,x,y;
    char op;
    for( int i = 1 ; i <= m ; i ++ )
    {
        cin >> op;
        if( op == 'C' )
        {
            cin >> x >> y;
            ls[++ siz] = y;
            M ++;
            q[M].op = 1;
            q[M].x = x;
            q[M].y = a[x];
            M ++;
            q[M].op = 0;
            q[M].x = x;
            q[M].y = y;
            a[x] = y;
        }
        else
        {
            M ++;
            M2 ++;
            cin >> l >> r >> k;
            q[M].op = 2;
            q[M].id = M2;
            q[M].l = l;
            q[M].r = r;
            q[M].k = k;
        }
    }
    sort( ls + 1 , ls + siz + 1 );
    siz = unique( ls + 1 , ls + siz + 1 ) - ls - 1;
    for( int i = 1 ; i <= M ; i ++ )
        if( q[i].op == 0 || q[i].op == 1 )
            q[i].y = lower_bound( ls + 1 , ls + siz + 1 , q[i].y ) - ls;
    solve( 1 , siz , 1 , M );
    for( int i = 1 ; i <= M2 ; i ++ )
        cout << ls[ans[i]] << '\n';
    return 0;
}
