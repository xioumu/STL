/*==================================================* 
 | KMP 匹配算法O(M+N) 
 | CALL: res=kmp(str, pat);  原串为str; 模式为pat(长为P);  
\*==================================================*/ 
int  fail[P]; 
int  kmp(char* str, char* pat){ 
    int  i, j, k; 
    memset(fail, -1, sizeof (fail)); 
    for  (i = 1; pat[i]; ++i) { 
        for  (k=fail[i-1]; k>=0 && pat[i]!=pat[k+1]; 
                k=fail[k]); 
        if (pat[k + 1] == pat[i]) fail[i] = k + 1; 
    } 
    i = j = 0; 
    while ( str[i] && pat[j] ){  // By Fandywang  
        if ( pat[j] == str[i] ) ++i, ++j; 
        else if (j == 0)++i;//第一个字符匹配失败，从str 下个字符开始
        else  j = fail[j-1]+1;    } 
    if(   pat[j] )  return  -1;  
    else return i-j; 
} 

