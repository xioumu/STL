#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 50010
using namespace std;
struct point
{
    int x,y;
    point(int _x=0,int _y=0) : x(_x),y(_y) {}
    void input() { scanf("%d%d",&x,&y); }
};
point operator-(const point &p1,const point &p2)
{  return point(p1.x-p2.x, p1.y-p2.y);
}
int operator*(const point &p1,const point &p2)
{  return p1.x*p2.y - p1.y*p2.x;
}
bool operator<(const point &p1,const point &p2)
{  if(p1.x != p2.x) return p1.x < p2.x;
   else return p1.y < p2.y;
}
int n,tn;
point a[MAXN],tu[MAXN];
void init()
{
    int i,j,k,r,w;
    for(i=1;i<=n;i++)
       a[i].input();  
}
void tubao()
{
    int i,j,k,r,w,un,dn;
    point dd[MAXN],du[MAXN];
    sort(a+1,a+n+1);
    un = dn = 2;
    dd[1] = du[1] = a[1];
    dd[2] = du[2] = a[2];
    
    for(i=3;i<=n;i++)
    {  for(;un > 1 && (du[un] - du[un-1]) * (a[i] - du[un]) > 0;un--);
       for(;dn > 1 && (dd[dn] - dd[dn-1]) * (a[i] - dd[dn]) < 0;dn--);
       du[++un] = a[i];
       dd[++dn] = a[i];
    }
    tn = 0;
    for(i=1;i<un;i++)  tu[++tn] = du[i];
    for(i=dn;i>1;i--)  tu[++tn] = dd[i];
}
int dis(point p1, point p2)
{
    return (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);
}
int myabs(int x)
{    if(x < 0) x = -x;
     return x;
}
void solve()
{
    int i,j,k,r,w,old=0;
    int ans=0;
    tubao();
    tu[0] = tu[tn];
    tu[tn+1] = tu[1];
    for(i=1,j=1;i<=tn;i++)
    {  old = j;
        while(  myabs( (tu[i+1]-tu[i]) * (tu[j]-tu[i]) )<=
                myabs( (tu[i+1]-tu[i]) * (tu[j+1]-tu[i]) ))
        {   ans = max(ans, dis(tu[i],tu[j]) );
            j = j % tn + 1;
            if( j== old) break;
        }
        ans = max(ans, dis(tu[i],tu[j]) );
    }
    printf("%d\n",ans);
}
int main()
{
    freopen("p2187.in","r",stdin);
    while(scanf("%d",&n) != EOF)
    {  init();
       solve();
    }
    return 0;
}
