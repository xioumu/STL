void getrmq(int *height, int n, int rmq[50][MAXN]){
    int i,j,k,r,w,m;
    m = (double)log((double)n + 1) / (double)log(2.0);
    for(i=0; i<=m; i++)
        for(j=0; j<=n; j++)
            rmq[i][j] = MAXNUM;
    for(i=0; i<=n; i++)  rmq[0][i] = height[i];
    for(i=1; i<=m; i++)
        for(j=0; j<=n - (1<<(i-1)) + 1; j++)
            rmq[i][j] = min(rmq[i-1][j], rmq[i-1][j + (1 << (i - 1) ) ]);
}
int find(int rmq[50][MAXN], int l, int r){
    int m = (double)log((double)r - l + 1) / (double)log(2.0);
    return min(rmq[m][l], rmq[m][r - (1<<m) + 1]);
}

