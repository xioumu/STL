long long v[MAXN],dis[MAXN],dui[MAXN],rear,front,dn,b[MAXN];
void up(long long x)
{
     long long i,j,k;
     i = x/2; j = x;
     while(i >= 1)
     { 
        if(dis[ dui[j] ] < dis[ dui[i] ] ) { swap(&dui[j],&dui[i]); swap(&b[ dui[j] ],&b[ dui[i] ]);  }
        else break;
        j = i; 
        i /= 2;
     }
}
void jin(long long a) 
{    
     dui[++dn] = a;
     b[a] = dn;
     up(dn);
}
void chu(long long *a)
{
     long long i,j,k;
     *a = dui[1];
     swap(&dui[1],&dui[dn]);
     swap(&b[ dui[1] ],&b[ dui[dn] ]);
     dn--;
     i = 1;
     while(i<=dn/2)
     {  j = i*2;
        if(j+1<=dn && dis[ dui[j] ] > dis[ dui[j+1] ]) j++;
        if(dis[ dui[i] ] > dis[ dui[j] ]) { swap(&dui[i],&dui[j]); swap(&b[ dui[i] ],&b[ dui[j] ]); }
        else break;
        i = j;
     }
}
void dij(long long w)
{
     long long i,j,k,r;
     node *p;
     memset(v,0,sizeof(v));
     memset(dui,10,sizeof(dui));
     /*for(i=1;i<=s4;i++) dis[i] = MAXNUM;*/
     dn = 0;
     dis[w] = 0;
     for(i=1;i<=s4;i++) jin(i);
     for(i=1;i<=(n-1)*(n-1)+3;i++)
     {  chu(&k);  /*printf("%I64d:%I64d\n",k,dis[k]);*/
        for(p=g[k];p;p=p->next)
          if(dis[p->adj] > dis[k] + p->road)
          {  dis[p->adj] = dis[k] + p->road;
             up(b[p->adj]);
          }
     }
}

