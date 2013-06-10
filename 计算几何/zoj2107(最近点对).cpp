bool cmpy(const point &a, const point &b){
    if( sgn(a.y - b.y) != 0) return a.y < b.y;
    else return a.x < b.x;
}
bool cmpx(const point &a, const point &b){
    if( sgn(a.x - b.x) != 0) return a.x < b.x;
    else return a.y < b.y;
}
point tempt[maxn], a[maxn];
int n;
void get_min(point *a, int l, int r, double &d){
    int n = r - l + 1;
    if(n == 1) { return;}
    if(n <= 3){
        repf(i, l, r - 1){
            d = min(d, (a[i] - a[(i + 1)]).len());
        }
        d = min(d, (a[r] - a[l]).len());
    }
    else{
        double d1, d2, d3;
        d1 = d2 = d3 = 1e100;
        int mid = (l + r) >> 1;
        get_min(a, l, mid, d1);
        get_min(a, mid + 1, r, d2);
        d = min(d1, d2);
        int k = 0, num = 6;
        repf (i, l, r)
            if( fabs(a[i].x - a[mid].x) <= d) 
                tempt[k++] = a[i];
        sort(tempt, tempt + k, cmpy);
        rep (i, k)
            for(int j = i + 1; j < k && tempt[j].y - tempt[i].y < d; j++){
                d = min(d, (tempt[j] - tempt[i]).len());
            }
    }
}
int main(){ 
    while(scanf("%d", &n) == 1 && n){
        rep(i, n){
            point p;
            p.input();
            a[i] = p;
        }
        sort(a, a + n, cmpx);
        double ans = 1e100;
        get_min(a, 0, n - 1, ans);
        printf("%.2f\n", ans / 2);
    }
    return 0;
}
