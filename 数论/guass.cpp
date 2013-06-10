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
}
