/*
 * Author:  xioumu
 * Created Time:  2011-11-4 16:24:07
 * File Name: p1222.cpp
 */
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
int map[40][40];
int ans[40];
int n;

void init()
{
   int i,j,k,r,w;
   memset(map,0,sizeof(map));
   memset(ans,0,sizeof(ans));
   for(i=0;i<30;i++)
     scanf("%d",&map[i][30]);
   for(i=0;i<30;i++)
      for(j=0;j<30;j++)
      {  int x,y,xx,yy;
         x = i/6; y = i % 6;
         xx= j/6; yy= j % 6;
         if(abs(x-xx) + abs(y-yy)<= 1 ) 
            map[j][i] = 1;
      }
   
   //for(i=0;i<30;i++,printf("\n"))
      //for(j=0;j<=30;j++)
         //printf("%d",map[i][j]);
}
int gauss(int map[40][40],int ans[40])
{
   int i,j,k,r,w;
   for(k=0;k<30;k++)
   {  i = k;
      while(i<30 && map[i][k] == 0)  i++;
      if(i == 30) continue;
      if(i > k)
      {  for(j=0;j<=30;j++)
           swap(map[i][j],map[k][j]);
      }
      for(i=0;i<30;i++)
         if(map[i][k] && i != k)
         {  for(j=k;j<=30;j++)
               map[i][j] ^= map[k][j];
         }
   }
   
   for(k=29;k>=0;k--)
   {  ans[k] = map[k][30];
      for(i=0;i<=30 && !map[k][i];i++) ;
      if(i == 30) return 0;
      for(i=k+1;i<30;i++)
        ans[k] ^= map[k][i] * ans[i];
      //ans[k] ^= map[k][k];
   }
   
   return 1;
}
void solve()
{
   int i,j,k,r,w;
   if( !gauss(map,ans) ) 
      printf("error\n");
   for(i=0;i<30;i++)
   {  printf("%d ",ans[i]);
      if( (i+1) % 6 == 0) printf("\n");
   }
}
int main()
{
   int t,i;
   //freopen("p1222.in","r",stdin);
   scanf("%d",&t);
   for(i=1;i<=t;i++)
   {  init();
      printf("PUZZLE #%d\n",i);
      solve();
   }
   return 0;
}
