long dn=0;           /*´ó¸ù¶Ñ*/
void jia(long key)   
{ long i,j,k,m;
  a[++dn]=key; 
  i=dn/2; j=dn;
  while(i>=1)
  { if(a[j]>a[i]) swap(&a[j],&a[i]);
    else break;
    j=i; i/=2;
  }
} 
void del()
{ long i,j,k,m;
  swap(&a[1],&a[dn]);
  dn--;
  i=1; 
  while(i<=dn/2)
  { j=i*2;
    if(j+1<=dn&&a[j]<a[j+1]) j++;
    if(a[i]<a[j]) swap(&a[i],&a[j]);
    else break;
    i=j; 
  }
}

