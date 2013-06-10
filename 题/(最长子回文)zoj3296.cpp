/*
 * Author:  xioumu
 * Created Time:  2012-3-20 20:03:34
 * File Name: zoj3296.cpp
 * solve: zoj3296.cpp
 */
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<string>
using namespace std;
#define inf 1e-8
#define MAXN 100007
#define MAXNUM 200000000
typedef long long int64;
char s[MAXN];
int a[MAXN],fl[MAXN],fr[MAXN],sa[MAXN],myrank[MAXN],height[MAXN];
int wa[MAXN], wb[MAXN], wv[MAXN], wws[MAXN];
int rmq[50][MAXN];
int n,m,n1;
bool cmp(int *wb, int a, int b, int l, int n){
    int r,w;
    r = a + l >= n ? 0 : wb[a + l];
    w = b + l >= n ? 0 : wb[b + l];
    return wb[a] == wb[b]  && r == w;
}
void getsa(int *a, int n, int m, int *sa){
    int i,j,k,r,w,p;
    for(i=0; i<=m; i++) wws[i] = 0;
    for(i=0; i<n; i++)  wws[ wa[i] = a[i] ]++;
    for(i=1; i<=m; i++)  wws[i] += wws[i - 1];
    for(i=n-1; i>=0; i--)  sa[ --wws[ wa[i] ] ] = i;
    for(j=1,p=1; j<n && p<n; j*=2, m = p){
        for(i=n-j,p=0; i<n; i++)  wb[p++] = i;
        for(i=0; i<n; i++)  if(sa[i] >= j)  wb[p++] = sa[i] - j;
        for(i=0; i<=m; i++)  wws[i] = 0;
        for(i=0; i<n; i++)  wv[i] = wa[ wb[i] ];
        for(i=0; i<n; i++)  wws[ wv[i] ]++;
        for(i=1; i<=m; i++)  wws[i] += wws[i-1];
        for(i=n-1; i>=0; i--)  sa[ --wws[ wv[i] ] ] = wb[i];
        for(i=0; i<n; i++)  wb[i] = wa[i];
        for(i=1,p=1,wa[ sa[0] ] = 0; i<n; i++)
            wa[ sa[i] ] = cmp(wb, sa[i], sa[i-1], j, n) ? p - 1 : p++;
    }
}
void getheight(int *a, int *sa, int n, int *height){
    int i,j,k,r,w;
    k = 0; 
    for(i=0; i<=n; i++)  myrank[ sa[i] ] = i;
    for(i=0; i<n; height[ myrank[i++] ] = k)
        for(k ? k-- : 0, j = sa[ myrank[i] - 1]; a[i + k] == a[j + k]; k++);
}
void getrmq(int *height, int n, int rmq[50][MAXN]){
    int i,j,k,r,w,m;
    m = (double)log((double)n + 1) / (double)log(2.0);
    for(i=0; i<=m; i++)
        for(j=0; j<=n; j++)
            rmq[i][j] = MAXNUM;
    for(i=0; i<=n; i++)  rmq[0][i] = height[i];
    for(i=1; i<=m; i++)
        for(j=0; j<=n - (1<<(i-1)) + 1; j++)
            rmq[i][j] = min(rmq[i-1][j], rmq[i-1][j + (1 << (i - 1) ) ]);
}
int find(int rmq[50][MAXN], int l, int r){
    int m = (double)log((double)r - l + 1) / (double)log(2.0);
    return min(rmq[m][l], rmq[m][r - (1<<m) + 1]);
}
int lca(int rmq[50][MAXN], int l, int r){
    int ll = myrank[l],rr = myrank[r];
    if(ll > rr) swap(ll, rr);
    ll++;
    return find(rmq, ll, rr);
}
void init(){
    int i,j,k;
    n1 = n = strlen(s);
    for(i=0; i<n; i++)  a[i] = s[i];
    for(i=n+1; i<=n+n; i++)  a[i] = s[n + n - i];
    a[n] = 200;
    n = n + n + 1;
    a[n] = 0;
    getsa(a, n+1, 250, sa);
    getheight(a, sa, n, height);
    getrmq(height, n, rmq);
    memset(fl, 10, sizeof(fl));
    memset(fr, 0, sizeof(fr));
    for(i=0; i<n1; i++){
        k = lca(rmq, i, n - i - 1);
        fl[i] = i - k + 1;
        fr[i] = i + k - 1;
        k = lca(rmq, i, n - i - 2);
        fl[i] = min(fl[i], i - (k - 2));
        fr[i] = max(fr[i], i + (k - 1)); 
        //printf("%d : %d %d\n",i,fl[i],fr[i]);
    }
}
int z[MAXN],top;
void solve(){
    int i,j,k;
    int ans = top = 0;
    for(i=0; i<n1; i++){
        if(top != 0 && fr[ z[top] ] >= fr[i] )  continue;
        while(top != 0 && fl[i] <= fl[ z[top] ]) top--;
        while(top > 1 && fl[i] <= fr[ z[top-1] ] + 1 ) top--;
        z[++top] = i;
    }
    //for(i=1; i<=top; i++)   printf("%d ",z[i]);
    //printf("\n");
    printf("%d\n",top-1);
}
int main(){
    while(scanf("%s",s) != EOF){
        init();
        solve();
    }
    return 0;
}
