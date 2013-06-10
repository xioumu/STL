/*
 * Author:  xioumu
 * Created Time:  2011-11-15 13:05:57
 * File Name: p3335.cpp
 */
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
using namespace std;
#define MAXN 200
#define esp 1e-8
struct point{
   double x,y;
   point (double _x=0,double _y=0) : x(_x) , y(_y) {
   }
   void input(){
      scanf("%lf %lf",&x,&y);
   }
   double len() const{
      return sqrt(x*x + y*y);
   }
};
struct line{
   point s,e;
   double ang;
};
int n;
line b[MAXN];
int sgn(double x){
   return x > esp ? 1 : (x < -esp ? -1 : 0);
}
bool operator == (const point &p1,const point &p2){
   return sgn(p1.x-p2.x) == 0 && sgn(p1.y-p2.y) == 0;
}
point operator - (const point &p1,const point &p2){
   return point(p1.x-p2.x, p1.y-p2.y);
}
double operator * (const point &p1,const point &p2){
   return p1.x*p2.y - p1.y*p2.x;
}
bool para(line a,line b){
   return sgn((a.e-a.s) * (b.e-b.s)) == 0;
}
point JD(point a, point b, point c, point d){
   double d1 = (b-a)*(c-a),d2 = (b-a)*(d-a),
          d3 = (d-c)*(a-c),d4 = (d-c)*(b-c);
   return point( (c.x*d2 - d.x*d1) / (d2-d1),
                 (c.y*d2 - d.y*d1) / (d2-d1));
}
point JD(line a, line b){
   return JD(a.s, a.e, b.s, b.e);
}
void init() {
   int i,j,k;
   point a[MAXN];
   scanf("%d",&n);
   for(i=0;i<n;i++)
      a[i].input();
   a[n] = a[0];
   for(i=0;i<n;i++){
      b[i].s = a[i+1];
      b[i].e = a[i];
      b[i].ang = atan2(b[i].e.y - b[i].s.y, b[i].e.x - b[i].s.x);
   }
}
bool cmp(const line a, const line b){
   if(sgn(a.ang - b.ang) != 0) return a.ang < b.ang;
   else return sgn( (b.e - b.s) * (a.e - b.s) ) > 0;
}
line d[MAXN];
//存的是逆时针的多边形
int solve()
{
   int i,j,k,w;
   int r,f,t;
   t = 1;
   sort(b,b+n,cmp);
   for(i=1;i<n;i++)
      if(sgn(b[i].ang - b[i-1].ang) != 0) 
         b[t++] = b[i];
   if(t < 2) return 1;
   r = 1;   f = 0;
   d[0] = b[0];  d[1] = b[1];
   
   for(i=2;i<t;i++){
      if( para(d[r],d[r-1])  || para(d[f+1],d[f]) ) return 0;
      while(f < r && sgn( (b[i].e-b[i].s) * (JD(d[r],d[r-1]) - b[i].s) )< 0  ) r--;
      while(f < r && sgn( (b[i].e-b[i].s) * (JD(d[f],d[f+1]) - b[i].s) )< 0  ) f++;
      d[++r] = b[i];
   }
   while(f < r && sgn( (d[f].e-d[f].s) * (JD(d[r],d[r-1]) - d[f].s) ) < 0) r--;
   while(f < r && sgn( (d[r].e-d[r].s) * (JD(d[f],d[f+1]) - d[r].s) ) < 0) f++;
   return r > f+1;
}
int main()
{
   int t,i;
   scanf("%d",&t);
   for(i=1;i<=t;i++){
      init();
      if(solve() ) printf("YES\n");
      else printf("NO\n");
   }
   return 0;
}
