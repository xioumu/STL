int scanf(int &num)
{
    char in;
    while((in=getchar())!=EOF && (in>'9' || in<'0'));
    if(in==EOF) return 0;
    num=in-'0';
    while(in=getchar(),in>='0' && in<='9') num*=10,num+=in-'0';
    return 1;
}

