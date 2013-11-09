int scanf(int &num)
{
    char in;
    while((in=getchar())!=EOF && (in>'9' || in<'0'));
    if(in==EOF) return 0;
    num=in-'0';
    while(in=getchar(),in>='0' && in<='9') num*=10,num+=in-'0';
    return 1;
}

int scanf(int &num) { //¸ºÊı
    char in;
    int op = 1;
    while ((in = getchar()) != EOF && !(('0' <= in && in <= '9') || in == '-'));
    if (in == EOF) return 0;
    if (in == '-') {
        op = -1;
        in = getchar();
    }
    num = in - '0';
    while (in = getchar(), in >= '0' && in <= '9') num *= 10, num += in - '0';
    num *= op;
    return 1;
}
