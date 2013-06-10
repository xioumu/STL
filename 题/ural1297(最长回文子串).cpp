/*
 * Author:  xioumu
 * Created Time:  2012-3-16 1:00:23
 * File Name: ural1297.cpp
 * solve: ural1297.cpp
 */
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<string>
using namespace std;
#define inf 1e-8
#define MAXN 2007
typedef long long int64;
int a[MAXN], height[MAXN], myrank[MAXN], sa[MAXN];
int wa[MAXN], wb[MAXN], wv[MAXN], wws[MAXN];
int rmq[100][MAXN];
int n;
bool cmp(int *wb, int a, int b, int l, int n){
    int r,w;
    r = a + l >= n ? 0 : wb[a+l];
    w = b + l >= n ? 0 : wb[b+l];
    return wb[a] == wb[b] && r == w;
}
void getsa(int *a, int n, int m, int *sa){  //sa : 1 ~ n
    int i,j,k,r,w,p;
    for(i=0; i<=m; i++)  wws[i] = 0;
    for(i=0; i<n; i++)  wws[ wa[i] = a[i] ]++;
    for(i=1; i<=m; i++) wws[i] += wws[i-1];
    for(i=n-1; i>=0; i--)   sa[ --wws[ wa[i] ] ] = i;
    for(j=1,p=1; j<n&&p<n; j*=2,m=p){        //特别注意要写m=p
        for(i=n-j,p=0; i<n; i++)  wb[p++] = i;
        for(i=0; i<n; i++)  if(sa[i] >= j)  wb[p++] = sa[i] - j;
        for(i=0; i<=m; i++)   wws[i] = 0;
        for(i=0; i<n; i++)  wv[i] = wa[ wb[i] ];
        for(i=0; i<n; i++)  wws[ wv[i] ]++;
        for(i=1; i<=m; i++)  wws[i] += wws[i-1];
        for(i=n-1; i>=0; i--)   sa[ --wws[ wv[i] ] ] = wb[i];
        for(i=0; i<n; i++) wb[i] = wa[i];
        for(i=1,p=1,wa[ sa[0] ] = 0; i<n; i++)
            wa[ sa[i] ] = cmp(wb, sa[i], sa[i-1], j, n) ? p-1 : p++;
    }
}
void getheight(int *a, int *sa, int n, int *height){
    int i,j,k,r,w;
    k = 0;
    for(i=0; i<=n; i++)  myrank[ sa[i] ] = i;
    for(i=0; i<n; height[ myrank[i++] ] = k)
        for(k ? k-- : 0, j = sa[ myrank[i] - 1]; a[i+k] == a[j+k]; k++);
}
void getrmq(int *height, int n, int rmq[100][MAXN]){
    int i,j,k,r,m;
    m = (double)log((double)n + 1) / (double)log(2.0);
    for(i=0; i<=m; i++)
        for(j=0; j<=n; j++)
            rmq[i][j] = 200000000;
    for(i=0; i<=n; i++){
        rmq[0][i] = height[i];
    }
    for(i=1; i<=m; i++)
        for(j=0; j<=n - (1<<(i-1)) + 1; j++)
            rmq[i][j] = min(rmq[i-1][j], rmq[i-1][j + ( 1 << (i-1) )]);
}
int find(int rmq[100][MAXN], int l, int r){
    if(l > r)  swap(l, r);
    l++;
    int m = (double)log((double)r - l + 1) / (double)log(2.0);
    return min(rmq[m][l], rmq[m][r - (1 << m) + 1]);
}
int main(){
    char s[MAXN];
    int i,j,k;
    while(scanf(" %s",s) != EOF){
        memset(a,0,sizeof(a));
        n = strlen(s);
        for(i=0; i<n; i++)  a[i] = s[i];
        a[n] = 200;    
        for(i=n+1; i<=n+n; i++)  a[i] = s[n + n - i];
        a[n+n+1] = 0;
        getsa(a, n+n+2, 300, sa); 
        getheight(a, sa, n+n+1, height);
        getrmq(height, n+n+1, rmq);
        int ans = -1, ansb;
        for(i=0; i<n; i++){
            k = find(rmq, myrank[i], myrank[n + n - i]);
            if(ans < 2*k - 1){
                ans = 2 * k - 1;
                ansb = i - k + 1;
            }
            k = find(rmq, myrank[i], myrank[n + n - i - 1]);
            if(ans < (k-1) * 2 ){
                ans = (k-1) * 2;
                ansb = i - (k-2);
            printf("\n");
            }
        }
        for(i=ansb; i<ansb + ans; i++)
            printf("%c",a[i]);
        printf("\n");
    }
    return 0;
}
