/* 小的在左，大的在右。 */
#include"stdio.h"
#define NEWS (avltree *)malloc(sizeof(avltree))
typedef struct avltree
{ struct avltree *rc,*lc;
  long height,data,h,gao;
}avltree;
  FILE *input,*output;
long max(long a,long b) { if(a>b) return a; else return b;}
long min(long a,long b) { if(a<b) return a; else return b;}
long mheight(avltree *t){ if(t==NULL) return 0; else return t->height;  }
avltree *singleft(avltree *t)
{ avltree *a;
  a=t->lc;
  t->lc=a->rc;
  a->rc=t;
  
  t->height=max(mheight(t->lc),mheight(t->rc))+1;
  a->height=max(mheight(a->lc),mheight(a->rc))+1;
  return a;	
}
avltree *singright(avltree *t)
{ avltree *p;
  p=t->rc;
  t->rc=p->lc;
  p->lc=t;
  
  t->height=max(mheight(t->lc),mheight(t->rc))+1;
  p->height=max(mheight(p->lc),mheight(p->rc))+1;
  return p;
}
avltree *douleft(avltree *t)
{ t->lc=singright(t->lc);
  t=singleft(t);
  return t;
}
avltree *douright(avltree *t)
{ t->rc=singleft(t->rc);
  t=singright(t);
  return t;
}
avltree *insert(avltree *t,long key)
{ long i,j,k,r,w;
  avltree *p;
  if(t==NULL)
  { p=NEWS;
    p->height=1;
    p->data=key;
    p->lc=p->rc=NULL;
    return p;
  }
  if(key>t->data)
  { t->rc=insert(t->rc,key);
    if(mheight(t->rc) - mheight(t->lc) ==2) 
    { if(key>t->rc->data) t=singright(t);
      else t=douright(t);       
    }
  }
  else if(key<t->data)
  { t->lc=insert(t->lc,key);
    if(mheight(t->lc) - mheight(t->rc) ==2)
    { if(key<t->lc->data) t=singleft(t);
      else t=douleft(t);
    }
  }
  t->height=max(mheight(t->lc),mheight(t->rc))+1;
  return t;
}

int main()
{ long i,j,k,r,w,n;
  avltree *t=NULL;
  FILE *input,*output;
  input=fopen("avl.in","r");
  output=fopen("avl.out","w");
  fscanf(input,"%ld",&n);
  for(i=1;i<=n;i++)
  { fscanf(input,"%ld",&r);
    t=insert(t,r);  
  }  
  fclose(input);
  fclose(output);
  return 0;
}


