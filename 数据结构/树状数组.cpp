int f[maxn];
int lowb(int t) { return t & (-t); }
void add(int *f, int i, int value){   // index : 1 ~ n
    for(; i < n; f[i] += value, i += lowb(i) );
}
int getsum(int *f, int i){
    int s = 0;
    for(; i > 0; s += f[i], i -= lowb(i));
    return s;
}
