long long Gcd(long long a,long long b)
{
    for(long long t=a%b;t; a=b,b=t,t=a%b); return b;
}
long long ExpandGcd(long long a, long long b, long long &d, long long &x, long long &y)
{
    if( b ) { ExpandGcd( b, a%b , d, y, x); y -= a/b * x; }
    else { d = a; x = 1; y = 0; }
}

