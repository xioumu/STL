/*
 * Author:  xioumu
 * Created Time:  2012/7/22 16:00:47
 * File Name: f.cpp
 * solve: f.cpp
 */
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<string>
#include<map>
#include<set>
#include<vector>
using namespace std;
#define sz(v) ((int)(v).size())
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define repf(i, a, b) for (int i = (a); i <= (b); ++i)
#define repd(i, a, b) for (int i = (a); i >= (b); --i)
typedef long long lint;
const int maxint = -1u>>1;
const double esp = 1e-9;
const int maxn = 100003;
const double pi = acos(-1.0);
int sgn(double x){
    return (x > esp) - (x < -esp);
}
struct point{
    double x, y;
    point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    point operator - (const point &p) const {
        return point(x - p.x, y - p.y);
    }
    point operator + (const point &p) const {
        return point(p.x + x, p.y + y);
    }
    double operator * (const point &p) const {
        return x * p.y - y * p.x;
    }
    point operator * (const double &p) const {
        return point(x * p, y * p);
    }
    point operator / (const double &p) const {
        return point(x / p, y / p);
    }
    double operator ^ (const point &p) const {
        return x * p.x + y * p.y;
    }
    double len(){
        return sqrt(x * x + y * y);
    }
    int input(){
       return scanf("%lf%lf", &x, &y);
    }
    void output(){
       printf("%f %f\n", x, y);
    }
    point set(){
        double l = sqrt(x * x + y * y);
        return point(x / l, y / l);
    }
    bool operator < (const point &p) const{
        if(sgn(x - p.x) != 0) return x < p.x;
        else return y < p.y;
    }
    bool operator == (const point &p) const {
        return sgn(p.x - x) == 0 && sgn(p.y - y) == 0;
    }
};
bool cmpy(const point &a, const point &b){
    if( sgn(a.y - b.y) != 0) return a.y < b.y;
    else return a.x < b.x;
}
bool cmpx(const point &a, const point &b){
    if( sgn(a.x - b.x) != 0) return a.x < b.x;
    else return a.y < b.y;
}
point tempt[maxn], a[maxn];
int n;
void get_min(point *a, int l, int r, double &d){
    int n = r - l + 1;
    if(n == 1) { return;}
    if(n <= 3){
        repf(i, l, r - 1){
            d = min(d, (a[i] - a[(i + 1)]).len());
        }
        d = min(d, (a[r] - a[l]).len());
    }
    else{
        double d1, d2, d3;
        d1 = d2 = d3 = 1e100;
        int mid = (l + r) >> 1;
        get_min(a, l, mid, d1);
        get_min(a, mid + 1, r, d2);
        d = min(d1, d2);
        int k = 0, num = 6;
        repf (i, l, r)
            if( fabs(a[i].x - a[mid].x) <= d) 
                tempt[k++] = a[i];
        sort(tempt, tempt + k, cmpy);
        rep (i, k)
            //repf (j, i + 1, min(i + num, k - 1)){
                //d = min((a[i] - a[j]).len(), d);
            //}
        
        for(int j = i + 1; j < k && tempt[j].y - tempt[i].y < d; j++){
                d = min(d, (tempt[j] - tempt[i]).len());
            }
    }
}
int main(){ 
    while(scanf("%d", &n) == 1 && n){
        rep(i, n){
            point p;
            p.input();
            a[i] = p;
        }
        sort(a, a + n, cmpx);
        double ans = 1e100;
        get_min(a, 0, n - 1, ans);
        printf("%.2f\n", ans / 2);
    }
    return 0;
}
