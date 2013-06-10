#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 1007
using namespace std;
int a[MAXN][MAXN],f[MAXN];
int n,m,ans;
void init(){
   int i,j,k,r,w;
   for(i=1;i<=n;i++)
      for(j=i+1;j<=n;j++)
         a[i][j] = a[j][i] = 1;
   for(i=1;i<=m;i++){
      scanf("%d %d",&r,&w);
      a[r][w] = a[w][r] = 0;
   }
}
int zhan[MAXN],top,v[MAXN],df[MAXN],low[MAXN],num;
int d[MAXN];
bool pan(int w)
{
   int i,j,k;
   for(i=1;i<=n;i++){
      if(a[w][i] && v[i] != 0){
         if(v[i] == 1){
            v[i] = (v[w]-1)%2 + 2;
            if( !pan(i) ) return false;
         }
         else if( (v[w]-1)%2 + 2 != v[i])
            return false;
      }
   }
   return true;
}
void dfs(int w,int fa){
   int i,j,k,r;
   df[w] = low[w] = ++num;
   zhan[++top] = w;
   for(i=1;i<=n;i++)
      if(a[w][i] && i != fa){
         if(df[i] == 0){
            dfs(i,w);
            low[w] = min(low[w],low[i]); 
            if(low[i] >= df[w]){
               memset(v,0,sizeof(v));
               k = top;
               do{
                  v[ zhan[top] ] = 1;
                  top--;
               }while(zhan[top+1] != i);
               v[w]=1;
               
               if(!pan(w) ){
                  for(k=1;k<=n;k++)
                     if(v[k] >= 1) {
                        d[k] = 1;
                     }
               }
               
            }     
         }
         else low[w] = min(low[w],df[i]);
      }
   
}
void solve(){
   int i,j,k,r,w;
   ans = 0;
   memset(f,0,sizeof(f));
   top = num = 0;
   memset(df,0,sizeof(df));
   memset(low,0,sizeof(low));
   memset(v,0,sizeof(v));
   memset(d,0,sizeof(d));
   for(i=1;i<=n;i++){
      if(df[i] == 0){
         dfs(i,0);
      }
   }
   for(i=1;i<=n;i++)
      if(d[i] == 0){
         //printf("%d\n",i);
         ans++; 
      }
   printf("%d\n",ans);
}
int main()
{
   while(scanf("%d %d",&n,&m) != EOF && n && m){
      init();
      solve();
   }
   return 0;
}


