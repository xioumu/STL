double f(double x) {
	return x;
}
double sps(double l, double r){
    return (f(l) + f(r) + f((l+r)/2)*4)/6 * (r - l);
}
double sps2(double l, double r, int dep){
    //printf("%lf %lf %d\n", l, r, dep);
    double cur = sps(l, r), mid = (l + r)/2;
    double y = sps(l, mid) + sps(mid, r);
    if(sgn(cur-y) == 0 && dep > 9) return cur;
    return sps2(l, mid, dep+1) + sps2(mid, r, dep+1);
}
