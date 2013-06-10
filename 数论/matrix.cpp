struct matrix {
    double ar[maxa][maxa];
    int n, m ; // n * m; 0 ~ n - 1, 0 ~ m - 1;
    matrix() {
        n = 4; //n
        m = 4; //m
        memset(ar, 0, sizeof(ar));
    }
    void clear() {
        rep (i, n)
            rep (j, m)
                ar[i][j] = 0;
    }
    void set_one() { //记得先给N,M赋值
        rep (i, n)
            rep (j, m)
                ar[i][j] = 0;
        rep (i, min(n, m))
            ar[i][i] = 1;
    }
    void output() {
        printf("%d %d\n", n, m);
        rep(i, n) {
            rep(j, m)
                printf("%.3f ", ar[i][j]);
            printf("\n");
        }
        printf("\n");
    }
};
matrix operator * (const matrix &a, const matrix &b) {
    matrix c;
    if(a.m != b.n) printf("a.m != b.n\n");
    c.clear();
    c.n = a.n;
    c.m = b.m;
    rep (i, a.n)  
        rep (j, b.m)  
        rep (k, a.m) {
            c.ar[i][j] += a.ar[i][k] * b.ar[k][j];   //mod
        }
    return c;
}

