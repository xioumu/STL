/*
 * Author:  xioumu
 * Created Time:  2013/10/1 15:01:03
 * File Name: 2104.cpp
 * solve: 2104.cpp
 */
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<string>
#include<map>
#include<set>
#include<iostream>
#include<vector>
#include<queue>

using namespace std;
#define sz(v) ((int)(v).size())
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define repf(i, a, b) for (int i = (a); i <= (b); ++i)
#define repd(i, a, b) for (int i = (a); i >= (b); --i)
#define clr(x) memset(x,0,sizeof(x))
#define clrs( x , y ) memset(x,y,sizeof(x))
#define out(x) printf(#x" %d\n", x)
#define sqr(x) ((x) * (x))
typedef long long lint;

const int maxint = -1u>>1;
const double eps = 1e-8;
const int maxn = 100000 + 10;
const int maxt = 20 * maxn;

int sgn(const double &x) {  return (x > eps) - (x < -eps); }

struct node {
    int l, r, lc, rc, val;
};

node t[maxt];
int orl[maxn], root[maxn], xx[maxn];
int tn, n, m, xn;
map<int, int> mp;

int build(int l, int r) {
    if (l > r) return 0;
    int w = ++tn; 
    t[w].l = l; t[w].r = r; t[w].lc = t[w].rc = 0; 
    t[w].val = 0;
    if (l == r) return w;
    int mid = (l + r) >> 1;
    t[w].lc = build(l, mid);
    t[w].rc = build(mid + 1, r);
    return w;
} 

int change(int ow, int k, int val) {
    int w = ++tn;
    t[w].l = t[ow].l, t[w].r = t[ow].r;
    t[w].lc = t[ow].lc; t[w].rc = t[ow].rc;
    t[w].val = t[ow].val + val;
    int mid = (t[w].l + t[w].r) >> 1;
    if (t[w].l == t[w].r) return w;
    if (k <= mid) 
        t[w].lc = change(t[ow].lc, k, val);
    else t[w].rc = change(t[ow].rc, k, val);
    return w;
}

int que(int ow, int w, int k) {
    //if (ow == 0 || w == 0) return 0;
    int h = t[t[w].lc].val - t[t[ow].lc].val;
    if (t[w].l == t[w].r) return t[w].l;
    if (k <= h) 
        return que(t[ow].lc, t[w].lc, k);
    else 
        return que(t[ow].rc, t[w].rc, k - h);
}

inline int bin(int x){
    int l=0, r=xn - 1, mid;
    while(l<=r){
        mid=(l+r)>>1;
        if(xx[mid] == x) return mid;
        if(x < xx[mid]) r = mid-1;
        else l=mid+1;
    }
    return 0;
}

int main() {
    int T;
    //scanf("%d", &T);
    //while (scanf("%d%d", &n, &m) == 2) {
    scanf("%d%d", &n, &m);
        mp.clear();
        tn = 0;
        rep (i, n) {
            scanf("%d", &orl[i]); 
            xx[i] = orl[i];
        } 
        xn = n;
        sort(xx, xx + n);
        xn = unique(xx, xx + n) - xx;
        rep (i, n)
            orl[i] = bin(orl[i]);
        clr(root);
        t[0].val = 0;
        root[0] = build(0, xn - 1); 
        repf (i, 1, n) { 
            root[i] = change(root[i - 1], orl[i - 1], 1);
        } 
        rep (i, m) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            int res = xx[que(root[x - 1], root[y], z)];
            printf("%d\n", res);
        }
    //} 
    return 0;
}
