void getff()
{
     long i,j,k,r,w,id,am,mx;
     long p;
     memset(s,0,sizeof(s));
     memset(ff,0,sizeof(ff));
     n = strlen(b);
     s[0] = '#';
     for(i=1;i<=2*n;i++) 
       if(i%2 == 1) s[i] = b[i/2];
       else s[i] = '#';  
     m = 2*n;   w = j = id = am= mx = 0; 
     p = 1;
     while(p < m) 
     {  if(mx > p) { ff[p] = min( ff[ id-(p-id) ] , ff[id] - (p-id));}
        else ff[p] = 1;
        
        for(;s[p + ff[p]] == s[p - ff[p]]; ff[p]++);
        
        if(ff[p] + p > mx)
        {  mx = ff[p] + p;
           id = p;
        }
        
        p++;
     }
     for(i=1;i<=m;i++) ff[i]--;
}
