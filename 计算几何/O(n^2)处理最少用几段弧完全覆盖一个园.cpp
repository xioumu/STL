struct node {
    double be, en; //开始的角度 与 结束的角度 （-pi ~ pi)
    node (double _be = 0, double _en = 0) : be(_be), en(_en){
    }
    bool operator < (const node &b) const {
        return sgn(be - b.be) < 0;
    }
} a[maxn], b[maxn];

node change(node p, double ang) {  //将角度转换成从ang度开始，需要转动多少度
    double be = p.be, en = p.en;
    be -= ang;
    while(sgn(be) < 0) be += 2 * pi;
    en -= ang;
    while(sgn(en) < 0) en += 2 * pi;
    if(sgn(en - be) < 0) en += 2 * pi;
    return node(be, en);
}


	     sort(a, a + n);
        rep (i, n)
            a[i + n] = a[i];
        int ans = maxint;
        rep (i, n) {
            rep (j, n) {
                b[j] =  change(a[i + j], a[i].be);
            }
            int res = 0, k = 0;
            double old = 0;
            while(k < n && sgn(old - 2 * pi) < 0) {
                double next = old;
                while(k < n && sgn(b[k].be - old) <= 0) {
                    if(sgn(b[k].en - next) > 0) 
                        next = b[k].en;
                    k++;
                }
                if(sgn(next - old) == 0 ) k = n + 1;
                res++;
                old = next;

            }
            if(sgn(old - 2 * pi) < 0)  {
                continue;
            }
            ans = min(ans, res);
        }
        if(ans == maxint) ans = -1;
        printf("%d\n", ans);

