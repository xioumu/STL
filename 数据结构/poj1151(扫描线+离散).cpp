#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
#define inf 1e-8
#define MAXN 2007
typedef long long int64;
int sgn(double x){
    return x > inf ? 1: (x < -inf ? -1 : 0);
}
struct node{
    double x,l,r;
    int t;
    node(double _l, double _r, double _x,int _t) : l(_l), r(_r), x(_x), t(_t) {}
    bool operator < (const node &b) const {
        return sgn(x- b.x) < 0;
    }
};
vector<node> a;
int lazy[MAXN];
int cut[MAXN];
double fx[MAXN],fy[MAXN],sum[MAXN],num[MAXN],y[MAXN],ww[MAXN];
int n,m;
void init(){
    int i,j,k,r,w;
    double x1,y1,x2,y2;
    double x[MAXN];
    memset(lazy,0,sizeof(lazy));
    m = 0;
    a.clear();
    for(i=0; i<n; i++){
        scanf("%lf %lf %lf %lf",&x1,&y1,&x2,&y2);
        a.push_back( node(y1, y2, x1, 1) );
        a.push_back( node(y1, y2, x2, -1) );
        y[++m] = y2;
        x[m] = x1;
        y[++m] = y1;
        x[m] = x2;
    }
    sort(a.begin(), a.end());
    sort(y+1, y+m+1);
    fy[1] = y[1];
    w = 1;
    for(i=2; i<=m; i++){
        if(sgn(y[i] - y[i-1]) != 0)
            fy[++w] = y[i];        
    }
    memcpy(y, fy, sizeof(y));
    m = w;
    memset(fy,0,sizeof(fy));
    for(i=1; i<m; i++)
        fy[i] = fy[i-1] + y[i+1] - y[i];
    
    memset(num, 0, sizeof(num));
    for(i=1; i<=m; i++)
        num[i] = fy[i]; 
}
void getch(int t, int &lc, int &rc){
    lc = t<<1;
    rc = t<<1 | 1;
}
void add(int t, int ll, int rr, int l, int r, int h){
    int lc,rc,mid;
    if(rr < l || r < ll) return;
    getch(t, lc, rc);
    if(l <= ll && rr <= r){
        cut[t] += h;
        if(cut[t] >= 1){
            sum[t] = num[rr] - num[ll-1]; 
        }
        else if(ll == rr) sum[t] = 0;
        else sum[t] = sum[lc] + sum[rc];
        return ;
    }
    mid = (ll + rr) >> 1;
    add(lc, ll, mid, l, r, h);
    add(rc, mid+1, rr, l, r, h);
    if(cut[t] >= 1){
        sum[t] = num[rr] - num[ll-1]; 
    }
    else sum[t] = sum[lc] + sum[rc];
}
int find(double yy){
    int l,r,mid;
    l = 1; r = m;
    while(l <= r){
        mid = (l + r) / 2;
        if(sgn(y[mid] - yy) > 0) r = mid - 1;
        else if(sgn(y[mid] - yy) < 0) l = mid + 1;
        else return mid;
    }
    return -1;
}
void solve(){
    int i,j,k,r,l,w;
    memset(cut,0,sizeof(cut));
    memset(sum,0,sizeof(sum));
    memset(lazy,0,sizeof(lazy));
    memset(ww,0,sizeof(ww));
    double ans = 0;
    for(i=0; i<(int)a.size()-1; i++){
        l = find(a[i].l);
        r = find(a[i].r) - 1;
        if(l <= r) add(1, 1, m-1, l, r, a[i].t); 
        ans += sum[1] * (a[i+1].x - a[i].x);
    }
    printf("Total explored area: %0.2f\n",ans);
}
int main(){
    int ca = 1,ok=0;
    while(scanf("%d",&n) != EOF && n){
         if(ok == 1) printf("\n");
        init();
        printf("Test case #%d\n",ca++);
        solve();
        ok = 1;
    }
    return 0;
}
