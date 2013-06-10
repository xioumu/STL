/*
 * Author:  xioumu
 * Created Time:  2012-3-7 10:25:12
 * File Name: b.cpp
 * solve: 区间合并
 */
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<string>
using namespace std;
#define inf 1e-8
#define MAXN 50007
typedef long long int64;
struct node{
    int llen,rlen,lazy,mm;
    node() { llen = rlen = lazy = 0;}
};
node e[MAXN*4];

int n,m;
void getch(int t, int& cl, int &cr){
    cl = t << 1;
    cr = t << 1 | 1;
    //printf("%d %d %d\n",t,cl,cr);
}
void downdata(int t, int cl, int cr, int x, int y){
    int mid = (x+y) >> 1;
    e[t].llen = e[cl].llen;
    if(e[cl].llen == mid - x + 1)
        e[t].llen += e[cr].llen;
    
    e[t].rlen = e[cr].rlen;
    if(e[cr].rlen == y - mid)
        e[t].rlen += e[cl].rlen;
    
    e[t].mm = max(e[cl].mm, e[cr].mm);
    e[t].mm = max(e[t].mm, max(e[t].llen, e[t].rlen));
    e[t].mm = max(e[t].mm, e[cl].rlen + e[cr].llen);
}
void build(int t, int x, int y){
    int mid,cl,cr;
    if(x == y){
        e[t].llen = e[t].rlen = 1;
        e[t].lazy = -1;
        e[t].mm = 1;
        return;
    }
    e[t].lazy = -1;
    mid = (x+y)>>1;
    getch(t, cl, cr);
    build(cl, x, mid);
    build(cr, mid+1, y);
    downdata(t, cl, cr, x, y);
}
void updata(int t, int lc, int rc, int x, int y){
    int mid = (x+y) >> 1,k;
    k = e[t].lazy;
    e[lc].llen = e[lc].rlen = e[lc].mm = k * (mid - x + 1);
    e[rc].llen = e[rc].rlen = e[rc].mm = k * ( y - mid);
    e[lc].lazy = e[rc].lazy = e[t].lazy;
    e[t].lazy = -1;
}
int quert(int t, int x, int y, int h){
    int mid,cl,cr,k;
    mid = (x+y) >> 1;
    getch(t, cl, cr);
    if(e[t].mm < h) return 0;
    if(e[t].llen >= h){
        return x;
    }
    if(e[t].lazy != -1 && x != y)
        updata(t, cl, cr, x, y);
    k = 0;
    if(y != x) k = quert(cl, x, mid, h);
    if(k != 0) return k;
    
    if(e[cl].rlen + e[cr].llen >= h) 
       return mid - e[cl].rlen + 1; 
    
    if(x != y) k = quert(cr, mid+1, y, h);
    if(k != 0) return k;
    
    if(x != y) downdata(t, cl, cr, x, y);
    return 0;  
}
void add(int t, int x, int y, int a, int b, int w){
    int mid, cl, cr;
    if(x > b || y < a) return; 
    //printf("%d %d %d %d\n",x,y,a,b);
    if(a <= x && y <= b){
        e[t].lazy = w;
        e[t].llen = e[t].rlen = e[t].mm = (y - x + 1) * w;
        return ;
    }
    mid = (x + y) >> 1;
    getch(t, cl ,cr);
    if(e[t].lazy != -1 && x != y)
        updata(t, cl, cr, x, y);
    add(cl, x, mid, a, b, w);
    add(cr, mid+1,y,a, b, w);
    downdata(t, cl, cr, x, y);
}
int main(){    
    while(scanf("%d %d",&n,&m) != EOF){
        int i,j,k,r,w;
        memset(e,0,sizeof(e));
        build(1, 1, n);
        for(i=1; i<=m; i++){
            scanf("%d",&k);
            if(k == 1){
                scanf("%d",&w);
                int a = quert(1, 1, n, w);
                
                //printf("%d==\n",e[1].mm);
                
                printf("%d\n",a);
                if(a != 0){
                    add(1, 1, n, a, a+w-1, 0);
                }
            }
            else{
                scanf("%d %d",&r,&w);
                add(1, 1, n, r, r + w - 1, 1);
            }
        }
    }
    return 0;
}

