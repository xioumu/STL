/*
 * Author:  xioumu
 * Created Time:  2012-3-15 18:49:32
 * File Name: poj1743(后缀数组--求最长不相交子串).cpp
 * solve: poj1743(后缀数组--求最长不相交子串).cpp
 */
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<string>
using namespace std;
#define inf 1e-8
#define MAXN 20007
typedef long long int64;
int a[MAXN],sa[MAXN],rank[MAXN],height[MAXN];
int wv[MAXN],ws[MAXN],wa[MAXN],wb[MAXN];
int n;
bool cmp(int *wb, int a, int b, int l, int n){
    int r,w;
    r = (a + l >= n ? 0 : wb[a+l]);
    w = (b + l >= n ? 0 : wb[b+l]);
    return wb[a] == wb[b] && r == w;
}
void getsa(int *a, int n, int m, int *sa){  //sa : 1 ~ n
    int i,j,k,r,w,p;
    for(i=0; i<=m; i++)  ws[i] = 0;
    for(i=0; i<n; i++)  ws[ wa[i] = a[i] ]++;
    for(i=1; i<=m; i++) ws[i] += ws[i-1];
    for(i=n-1; i>=0; i--)   sa[ --ws[ wa[i] ] ] = i;
    for(j=1,p=1; j<n&&p<n; j*=2,m=p){        //特别注意要写m=p
        for(i=n-j,p=0; i<n; i++)  wb[p++] = i;
        for(i=0; i<n; i++)  if(sa[i] >= j)  wb[p++] = sa[i] - j;
        for(i=0; i<=m; i++)   ws[i] = 0;
        for(i=0; i<n; i++)  wv[i] = wa[ wb[i] ];
        for(i=0; i<n; i++)  ws[ wv[i] ]++;
        for(i=1; i<=m; i++)  ws[i] += ws[i-1];
        for(i=n-1; i>=0; i--)   sa[ --ws[ wv[i] ] ] = wb[i];
        for(i=0; i<n; i++) wb[i] = wa[i];
        for(i=1,p=1,wa[ sa[0] ] = 0; i<n; i++)
            wa[ sa[i] ] = cmp(wb, sa[i], sa[i-1], j, n) ? p-1 : p++;
    }
}
void getheight(int *a, int *sa, int *height, int n){
    int i,j,k,r,w;
    k = 0;
    for(i=0; i<=n; i++)  rank[ sa[i] ] = i;
    for(i=0; i<n; height[ rank[i++] ] = k)  
        for( k ? k-- : 0, j = sa[ rank[i] - 1 ]; a[i+k] == a[j+k]; k++);
}
bool check(int *sa, int *height, int n, int key){
    int i,j,k,ma,mi;
    ma = mi = sa[1];
    for(i=2; i<=n; i++){
        if(height[i] < key)  ma = mi = sa[i];
        else {
            ma = max(ma, sa[i]);
            mi = min(mi, sa[i]);
            if(ma - mi > key) return true;  //看情况选> or >=
        }
    }
    return false;
}
int main(){
    while(scanf("%d",&n) != EOF && n){
        int i,j,k,w;
        memset(a,0,sizeof(a));
        n--;
        scanf("%d",&j);
        for(i=0; i<n; i++){
            scanf("%d",&k);
            a[i] = k - j + 100;
            j = k;
        }

        a[n] = 0;
        getsa(a, n+1, 200, sa);
        getheight(a, sa, height, n);
        int l,r,mid,ans = -1;
        l = 1; r = n/2;
        while( l <= r){
            mid = (l + r) >> 1;
            if( check(sa, height, n, mid) )  {  l = mid + 1; ans = mid;  }
            else r = mid-1;
        }
        if(ans >= 4) printf("%d\n",ans+1);
        else printf("0\n");
    }
    return 0;    
}
